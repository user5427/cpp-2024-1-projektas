CC = g++
SRC := $(wildcard *.cpp)
OBJ := $(SRC:%.cpp=%.o)
%.o: %.cpp
	$(CC) -c $<  -o $@

full: $(OBJ)
