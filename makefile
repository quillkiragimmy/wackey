all:=wackey
CC:=g++
FLAGS:=-O3
INC:=-I .
SRC:=$(wildcard *.cpp)
OBJ:=$(SRC:.cpp=.o)

wackey: $(OBJ)
	$(CC) -o $@ $(OBJ) $(FLAGS)

main.o: main.cpp c2k.h vk.h
	$(CC) $(INC) -c main.cpp

vk.o: vk.cpp vk.h c2k.h
	$(CC) $(INC) -c vk.cpp

wackey.o: wackey.h
	$(CC) $(INC) -c wackey.cpp

c2k.o: c2k.cpp
	$(CC) $(INC) -c c2k.cpp

clean:
	@rm -f wackey *.o 
	
