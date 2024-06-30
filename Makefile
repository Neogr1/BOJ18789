CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC = main.cpp table.cpp util.cpp sa/sa.cpp policy/randomNChange.cpp policy/pickBest.cpp
OBJ = $(SRC:.cpp=.o)
HEADERS = table.h util.h sa/sa.h policy/randomNChange.h policy/pickBest.h
TARGET = boj18789

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: all clean
