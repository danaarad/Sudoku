/* Copyright 2013, Gurobi Optimization, Inc. */

/* This example formulates and solves the following simple MIP model:

     maximize    x +   y + 2 z
     subject to  x + 2 y + 3 z <= 4
                 x +   y       >= 1
     x, y, z binary
*/

#include "gurobi.h"

#include <stdlib.h>
#include <stdio.h>

#include "settings.h"



int vcrToidx(int v, int c, int r, int dim){
	int idx = 0;
	idx += (v-1)*dim*dim;
	idx += c*dim;
	idx += r;
	return idx;
}

int get_gurobi_solution(double *sol, int *ConstraintsFromBoard, int block_h, int block_w){
  GRBenv   *env   = NULL;
  GRBmodel *model = NULL;

  int idx = 0, N = block_h*block_w, i = 0;
  int buff_size = 256, error = 0, optimstatus = 0;
  int v = 0, c = 0, r = 0, q = 0, p = 0;
  double num_vars = N*N*N;

  int *ind = (int *) calloc(N, sizeof(int));
  double *val = (double *) calloc(N, sizeof(double));
  char *vtype = (char *) calloc((int)num_vars, sizeof(char));
  char *const_name = (char *) calloc(buff_size, sizeof(char));

  if (!ind || !val || !vtype || !const_name) {
	  printf(CALLOC_ERROR);
	  return -1;
  }

  /* Create environment - log file is mip1.log */
  error = GRBloadenv(&env, "mip1.log");
  if (error) {
	  printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
	  free(ind);
	  free(val);
	  free(vtype);
	  free(const_name);
	  return -1;
  }

  /* Create an empty model named "mip1" */
  error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL);
  if (error) {
	  printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
	  GRBfreeenv(env); free(ind); free(val); free(vtype); free(const_name);
	  return -1;
  }


  /* Add variables */
  /* variable types - for x,y,z (cells 0,1,2 in "vtype") */
  for(i = 0; i < num_vars; ++i) {
	  vtype[i] = GRB_BINARY;
  }
  /* add variables to model */
  error = GRBaddvars(model, num_vars, 0, NULL, NULL, NULL, NULL, NULL, NULL, vtype, NULL);
  if (error) {
	  printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
	  GRBfreemodel(model); GRBfreeenv(env);
	  free(ind); free(val); free(vtype); free(const_name);
	  return -1;
  }

  /* Change objective sense to maximization */
  error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
  if (error) {
	  printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
	  GRBfreemodel(model); GRBfreeenv(env);
	  free(ind); free(val); free(vtype); free(const_name);
	  return -1;
  }

  /* update the model - to integrate new variables */

  error = GRBupdatemodel(model);
  if (error) {
	  printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
	  GRBfreemodel(model); GRBfreeenv(env);
	  free(ind); free(val); free(vtype); free(const_name);
	  return -1;
  }


  /* First constraint: for v in [1,N], sum(Xvcr) = 1
   * Each cell has only one value
   */
  for(c = 0; c < N; ++c) {
	  for (r = 0; r < N; ++r) {
		  for (v = 1; v <= N; ++v) {
			  ind[v-1] = vcrToidx(v, c, r, N);
			  val[v-1] = 1;
		  }
		  /* add constraint to model*/
		  sprintf(const_name, "oneValPerCell[%d,%d]", c, r);
		  error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, const_name);
		  if (error) {
			  printf("ERROR %d %s GRBaddconstr(): %s\n", error, const_name, GRBgeterrormsg(env));
			  GRBfreemodel(model); GRBfreeenv(env);
			  free(ind); free(val); free(vtype); free(const_name);
			  return -1;
		  }
	  }
  }


  /* Second constraint: for r in [0,N-1], sum(Xvcr) = 1
   * Each col has only one of each val
   */
  for(c = 0; c < N; ++c) {
	  for (v = 1; v <= N; ++v) {
		  for (r = 0; r < N; ++r) {
			  ind[r] = vcrToidx(v, c, r, N);
			  val[r] = 1;
		  }
		  /* add constraint to model */
		  sprintf(const_name, "oneOfValPerCol_v=%d_c=%d", v, c);
		  error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, const_name);
		  if (error) {
			  printf("ERROR %d %s GRBaddconstr(): %s\n", error, const_name, GRBgeterrormsg(env));
			  GRBfreemodel(model); GRBfreeenv(env);
			  free(ind); free(val); free(vtype); free(const_name);
			  return -1;
		  }
	  }
  }

  /* Third constraint: for c in [0,N-1], sum(Xvcr) = 1
   * Each row has only one of each val
   */
  for(r = 0; r < N; ++r) {
	  for (v = 1; v <= N; ++v) {
		  for (c = 0; c < N; ++c) {
			  ind[c] = vcrToidx(v, c, r, N);
			  val[c] = 1;
		  }
		  /* add constraint to model */
		  sprintf(const_name, "oneOfValPerRow_v=%d_r=%d", v, r);
		  error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, const_name);
		  if (error) {
			  printf("ERROR %d %s GRBaddconstr(): %s\n", error, const_name, GRBgeterrormsg(env));
			  GRBfreemodel(model); GRBfreeenv(env);
			  free(ind); free(val); free(vtype); free(const_name);
			  return -1;
		  }
	  }
  }

  /* Fourth constraint: for each block sum(Xvcr) = 1
   * Each value appears once in each block.
   */
	for (q = 0; q < N; q += block_w) {
		for (p = 0; p < N; p += block_h) {

			/*for every value*/
			for (v = 1; v <= N; ++v) {
				idx = 0;
				/* sum of every xy in the block = 1*/
				for(c = q; c < (q + block_w); ++c) {
					for (r = p; r < (p + block_h); ++r) {
						ind[idx] = vcrToidx(v, c, r, N);
						val[idx] = 1;
						idx++;
					}

				}
				/* add constraint to model */
				sprintf(const_name, "oneOfValPerBlock[%d,%d]", q, p);
				error = GRBaddconstr(model, N, ind, val, GRB_EQUAL, 1.0, const_name);
				if (error) {
					printf("ERROR %d %s GRBaddconstr(): %s\n", error, const_name, GRBgeterrormsg(env));
					GRBfreemodel(model); GRBfreeenv(env);
				    free(ind); free(val); free(vtype); free(const_name);
					return -1;
				}
			}
		}
	}

 /* Constraints from board: if node(c,r) = v, Xvcr = 1*/
	for(c = 0; c < N; ++c) {
	  for (r = 0; r < N; ++r) {
		  for (v = 1; v <= N; ++v) {
			  idx = vcrToidx(v, c, r, N);
			  if (ConstraintsFromBoard[idx]==1){
				  ind[0] = idx;
				  val[0] = 1;

				  sprintf(const_name, "ConstFromBoard(c_%d,r_%d,v_%d)", c, r, v);
				  error = GRBaddconstr(model, 1, ind, val, GRB_EQUAL, 1.0, const_name);
				  if (error) {
					  printf("ERROR %d %s GRBaddconstr(): %s\n", error, const_name, GRBgeterrormsg(env));
					  GRBfreemodel(model); GRBfreeenv(env);
					  free(ind); free(val); free(vtype); free(const_name);
					  return -1;
				  }
			  }
		  }
	  }
	}

  /* Optimize model - need to call this before calculation */
  error = GRBoptimize(model);
  if (error) {
	  printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
	  GRBfreemodel(model); GRBfreeenv(env);
	  free(ind); free(val); free(vtype); free(const_name);
	  return -1;
  }

  /* Write model to 'mip1.lp' - this is not necessary but very helpful */
  error = GRBwrite(model, "mip1.lp");
  if (error) {
	  printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
	  GRBfreemodel(model); GRBfreeenv(env);
	  free(ind); free(val); free(vtype); free(const_name);
	  return -1;
  }

  /* Get solution information */
  error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
  if (error) {
	  printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
	  GRBfreemodel(model); GRBfreeenv(env);
	  free(ind); free(val); free(vtype); free(const_name);
	  return -1;
  }

	if (optimstatus == GRB_OPTIMAL) {
		/* get the solution - the assignment to each variable */
		error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, num_vars, sol);
		if (error) {
			printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
			GRBfreemodel(model); GRBfreeenv(env);
			free(ind); free(val); free(vtype); free(const_name);
			return -1;
		}
	}

  /* print results
  printf("\nOptimization complete\n");

  solution found
  if (optimstatus == GRB_OPTIMAL) {
    printf("Solution found\n");
  }
  no solution found
  else if (optimstatus == GRB_INF_OR_UNBD) {
    printf("Model is infeasible or unbounded\n");
  }
  error or calculation stopped
  else {
    printf("Optimization was stopped early\n");
  } */

  /* IMPORTANT !!! - Free model and environment */
  GRBfreemodel(model);
  GRBfreeenv(env);
  free(ind);
  free(val);
  free(vtype);
  free(const_name);
  return optimstatus;
}