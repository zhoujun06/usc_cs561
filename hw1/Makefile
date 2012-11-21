CC=g++
CFLAGS=-c -g -Wall
LD=/usr/ccs/bin/ld
LDFLAGS=-L/usr/usc/lib 
OBJ=hw1

all : $(OBJ)

$(OBJ)	: main.o Problem.o MapNode.o Search.o
	$(CC)  main.o Problem.o MapNode.o Search.o -o $(OBJ)

main.o : main.cpp 
	$(CC) $(CFLAGS) main.cpp

MapNode.o : MapNode.cpp MapNode.h 
	$(CC) $(CFLAGS) MapNode.cpp

Problem.o : Problem.cpp Problem.h MapNode.o
	$(CC) $(CFLAGS) Problem.cpp

Search.o : Search.cpp Search.h Queue.h Problem.o
	$(CC) $(CFLAGS) Search.cpp

clean:
	@rm -f *.o $(OBJ)
