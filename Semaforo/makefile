CC=g++

ifeq ($(DEBUG),yes)
	CXXFLAGS=-std=c++11 -Wall -ggdb
else
	CXXFLAGS=-std=c++11 -O2
endif

OBJECTS=FuzzyValue.o FuzzySet.o MembershipFunction.o FuzzySemaforo.o Main.o

all: main

main: $(OBJECTS)
	g++ $(CXXFLAGS) -o $@ $^

clean:
	del /f /q *.o