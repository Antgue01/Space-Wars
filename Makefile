SOURCES=$(wildcard *.cc)
BIN=$(SOURCES:%.cc=%)
OBJ=$(SOURCES:%.cc=%.o)
CC=g++
CFLAGS= -g -Wall 
LIBS=`sdl2-config --cflags --libs` -lpthread -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

all: $(BIN)

%.o: %.cc Makefile
	$(CC) -c $(CFLAGS) -o $@ $< $(LIBS)

$(BIN):$(OBJ) 
	$(CC) $(CFLAGS) -o  main $(OBJ)  $(LIBS)


.PHONY: clean

clean:
	-rm $(BIN) $(OBJ)
