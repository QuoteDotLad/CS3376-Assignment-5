SHELL = /bin/sh
FLAGS = -Wall -g
CC = g++

all : TwoChildren ThreeChildren dynpipe

TwoChildren: TwoPipesTwoChildren.cpp
	     $(CC) $(FLAGS) -o $@ TwoPipesTwoChildren.cpp

ThreeChildren: TwoPipesThreeChildren.cpp
	     $(CC) $(FLAGS) -o $@ TwoPipesThreeChildren.cpp

dynpipe: DynPipe.cpp
	     $(CC) $(FLAGS) -o $@ DynPipe.cpp

clean:
	rm TwoChildren ThreeChildren dynpipe
