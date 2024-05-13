CC = g++
SRC := $(wildcard *.cpp)
OBJ := $(SRC:%.cpp=%.o)
%.o: %.cpp
	$(CC) -c $<  -o $@

rez: $(OBJ)
	$(CC) $(OBJ) -o rez.out
full: $(OBJ)
