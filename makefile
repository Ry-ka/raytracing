CXX = g++
CXXFLAGS = -std=c++17 -I eigen-master -O2
LDFLAGS = 
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = raytracer

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
