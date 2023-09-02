CPP_SRC=$(wildcard *.cpp)
HPP_SRC=$(wildcard *.hpp)
FLAGS=-Wextra -Wall -pedantic
CC=g++

main: $(CPP_SRC) $(HPP_SRC)
	$(CC) -o main $(CPP_SRC) $(FLAGS)