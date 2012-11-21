CC=g++
CFLAGS=-c -g -Wall -DEUC_INTEGER -DBIG_GX 
LD=/usr/ccs/bin/ld
LDFLAGS=-L/usr/usc/lib 
OBJ=hw2

all : $(OBJ)

$(OBJ)	: MapNode.o Problem.o Search.o main.o 
	$(CC)  main.o Problem.o MapNode.o Search.o -o $(OBJ)

MapNode.o : MapNode.cpp MapNode.h 
	$(CC) $(CFLAGS) MapNode.cpp

Problem.o : Problem.cpp Problem.h MapNode.o
	$(CC) $(CFLAGS) Problem.cpp

Search.o : Search.cpp Search.h Queue.h Problem.o
	$(CC) $(CFLAGS) Search.cpp

main.o : main.cpp 
	$(CC) $(CFLAGS) main.cpp

clean:
	@rm -f *.o $(OBJ)
