/*
 * parser.h
 *
 *  This is our parsing module, used to parse a line from the user.
 *  This interface contains the parse function that recieves a
 *  string and pointers,
 *  parses the string to command and parameters,
 *  and places values in given pointers.
 *
 *  parse returns 1 on success and 0 otherwise.
 *
 */

#ifndef PARSER_H_
#define PARSER_H_

int parse(char str[], command_e *command_pointer, char *x_pointer, char *y_pointer, char *z_pointer);

#endif /* PARSER_H_ */
