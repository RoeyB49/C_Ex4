CC = gcc
FLAGS = -Wall -g
AR=ar 

all: graph 
		
Ex4.o: Ex4.c 
	$(CC) $(FLAGS) -c Ex4.c
	
graph: Ex4.o 
	$(CC) $(FLAGS) Ex4.o -lm -o graph
	
.PHONY: clean all

clean:
	rm -f *.o *.a *.so stringProg		
