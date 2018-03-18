SRC=./src
BIN=./bin

build:
	@mkdir -p $(BIN)
	clang++ -std=c++11 $(SRC)/main.cpp -lSDL2 -o $(BIN)/app

run:
	$(BIN)/app
