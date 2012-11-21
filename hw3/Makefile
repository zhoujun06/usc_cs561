CC=g++
CFLAGS=-c -g -Wall -DWITH_ABP
LD=/usr/ccs/bin/ld
LDFLAGS=-L/usr/usc/lib 
OBJ=hw3

all : $(OBJ)

$(OBJ)	: Problem.o Search.o main.o 
	$(CC)  main.o Problem.o Search.o -o $(OBJ)

Problem.o : Problem.cpp Problem.h 
	$(CC) $(CFLAGS) Problem.cpp

Search.o : Search.cpp Search.h Problem.o
	$(CC) $(CFLAGS) Search.cpp

main.o : main.cpp 
	$(CC) $(CFLAGS) main.cpp

clean:
	@rm -f *.o $(OBJ)
