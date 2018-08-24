/*
 * file_handler.h
 *
 *  Created on: 10 баев 2018
 *      Author: yael sapir
 */

#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

int writeToFile (FILE *file_ptr, mode_e mode);
int readFromFile (char* filename);

#endif /* FILE_HANDLER_H_ */
