SRC=./src
BIN=./bin

build:
	@mkdir -p bin
	clang++ -std=c++11 $(SRC)/main.cpp -lSDL2 -o $(BIN)/main

arm:
	@mkdir -p bin
	clang++ -std=c++11 $(SRC)/arm.cpp -lSDL2 -o $(BIN)/arm

run:
	$(BIN)/arm