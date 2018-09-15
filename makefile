CC = gcc
EXEC = sudoku-console
OBJS = Action.o commands.o file_handler.o Game.o gurobi_c.o main.o parser.o printer.o solver.o stack.o
COMP_FLAGS = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors -g
GUROBI_COMP = -I /usr/local/lib/gurobi563/include
GUROBI_LIB = -L /usr/local/lib/gurobi563/lib -lgurobi56

all : sudoku-console
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm
main.o: main.c commands.h settings.h Game.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Action.o: Action.c settings.h Action.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
commands.o: commands.c commands.h settings.h Game.h Action.h solver.h printer.h file_handler.h parser.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
file_handler.o: file_handler.c file_handler.h Game.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Game.o: Game.c Game.h Action.h settings.h   
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
gurobi_c.o: gurobi_c.c gurobi_c.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
parser.o: parser.c parser.h settings.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
printer.o: printer.c printer.h 
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
solver.o: solver.c solver.h Game.h printer.h stack.h settings.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
stack.o: stack.c stack.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
	