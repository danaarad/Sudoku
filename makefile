CC = gcc
EXEC = sudoku
OBJS = Action.o arrayAux.o change.o commands.o commandsAux.o file_handler.o Game.o GameAux.o gurobi_c.o main.o mainAux.o Node.o parser.o printer.o solver.o stack.o
COMP_FLAGS = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I /usr/local/lib/gurobi563/include
GUROBI_LIB = -L /usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm
main.o: main.c Game_structs.h mainAux.h settings.h Game.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Action.o: Action.c Game_structs.h Node.h change.h settings.h Action.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
arrayAux.o: arrayAux.c 
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
change.o: change.c change.h settings.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
commands.o: commands.c settings.h Game.h Node.h Action.h solver.h printer.h arrayAux.h file_handler.h commandsAux.h change.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
commandsAux.o: commandsAux.c commandsAux.h printer.h Action.h Node.h Game.h change.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
file_handler.o: file_handler.c file_handler.h Node.h Game.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Game.o: Game.c Game.h Node.h Action.h settings.h GameAux.h arrayAux.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
GameAux.o: GameAux.c settings.h Game_structs.h arrayAux.h Node.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
gurobi_c.o: gurobi_c.c gurobi_c.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
mainAux.o: mainAux.c mainAux.h parser.h printer.h settings.h commands.h Game.h 
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Node.o: Node.c Node.h settings.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
parser.o: parser.c Game_structs.h settings.h parser.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
printer.o: printer.c printer.h Node.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
solver.o: solver.c solver.h Node.h Game.h printer.h stack.h settings.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
stack.o: stack.c stack.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
	