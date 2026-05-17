CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -O3 -march=native

SRC = board.cpp movegen.cpp spectra.cpp
OBJ = $(SRC:.cpp=.o)
BIN = spectra

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: $(BIN)
	./$(BIN)

clean:
	rm -f *.o $(BIN)

rebuild:
	$(MAKE) clean
	$(MAKE)
	$(MAKE) run
