# Makefile

CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++14
CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -std=c11

main : main.cpp
	$(CXX) $(CXXFLAGS) -g main.cpp -o main

clean :
	rm -f *.o *.out
	rm -f main