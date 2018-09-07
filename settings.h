/*
 * settings.h
 *
 *  Created on: Aug 10, 2018
 *      Author: Dana Arad
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#define MAX_COMMAND_SIZE 256
#define MAX_SIZE 1024
#define CALLOC_ERROR "Error: calloc has failed\n"
#define MALLOC_ERROR "Error: malloc has failed\n"
#define SCANF_ERROR "Error: scanf has failed\n"
#define INIT_ERROR "Error: init has failed\n"
#define DEFAULT_BLOCK_HEIGHT 3
#define DEFAULT_BLOCK_WIDTH 3


/* Gurobi Model status codes (after call to GRBoptimize()) */

#define GRB_LOADED          1
#define GRB_OPTIMAL         2
#define GRB_INFEASIBLE      3
#define GRB_INF_OR_UNBD     4
#define GRB_UNBOUNDED       5
#define GRB_CUTOFF          6
#define GRB_ITERATION_LIMIT 7
#define GRB_NODE_LIMIT      8
#define GRB_TIME_LIMIT      9
#define GRB_SOLUTION_LIMIT 10
#define GRB_INTERRUPTED    11
#define GRB_NUMERIC        12
#define GRB_SUBOPTIMAL     13
#define GRB_INPROGRESS     14

#endif /* SETTINGS_H_ */
