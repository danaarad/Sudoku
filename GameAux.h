/*
 * GameAux.h
 *
 *  Created on: 31 баев 2018
 *      Author: yael sapir
 */

#ifndef GAMEAUX_H_
#define GAMEAUX_H_

int updateErrorsFromCheckTable(Game *gp, int ***checkTable, int lenOfArr);

void freeCheckTable(int ***checkTable, int rowSize);

int ***callocCheckTable(int rowSize);

int resetCheckTable(int ***checkTable, int rowSize);


#endif /* GAMEAUX_H_ */
