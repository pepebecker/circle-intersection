NAME = app
SRC = ./src/*.c -I./include
SDL = ./sdl/*.c -lSDL2 -lSDL2_gfx
BIN = ./bin/$(NAME)
WASM = ./web/$(NAME).wasm
WASM_FLAGS = --target=wasm32 -nostdlib -Wl,--no-entry -Wl,--export-all

run: sdl
	$(BIN)

sdl: clean_sdl
	mkdir -p bin
	clang $(SRC) -o $(BIN) $(SDL)

wasm: clean_wasm
	mkdir -p web
	clang $(SRC) -o $(WASM) $(WASM_FLAGS)

clean: clean_sdl clean_wasm

clean_sdl:
	rm -rf $(BIN)

clean_wasm:
	rm -rf $(WASM)
