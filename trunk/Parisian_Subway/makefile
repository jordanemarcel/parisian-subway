#+-------------------------------------------+
#|               Makefile                    |
#|                                           |
#|Nom / Login : Clement Lebreton / clebre01  | 
#|		Jordane Marcel / jmarce01    |
#+-------------------------------------------+
#
SRCDIR=src/
BINDIR=bin/
INCDIR=include/
CC=gcc
CFLAGS =-I $(INCDIR) -Wall -ansi -pedantic
DIR=$(shell pwd)
SRC=$(SRCDIR)station_loader.c $(SRCDIR)adjacent_list.c $(SRCDIR)dijkstra.c $(SRCDIR)stack.c $(SRCDIR)hashmap.c $(SRCDIR)station.c $(SRCDIR)subway.c 
OBJ= $(SRC:.c=.o)


all: metro
		@echo "Compilation successfully completed."

metro: $(OBJ)
	$(CC) -o $(BINDIR)$@ $^

$(SRCDIR)%.o: $(SRCDIR)%.c
	$(CC) -o $@ -c $< $(CFLAGS)
clean:
	@echo Deleting files.
	rm -rf $(BINDIR)metro
	rm -rf $(SRCDIR)*.o


