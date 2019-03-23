SRC=main.c sdl-light.c
HEADERS=sdl-light.h
BIN=niveau1
LIBS=-L/usr/lib/x86_64-linux-gnu -lsndfile -lm

$(BIN): $(SRC) $(HEADERS) 
	gcc -Wall -g  -std=c99 $(SRC) -lm `sdl-config --cflags --libs` -o $(BIN)

clean:
	rm -f $(BIN)
