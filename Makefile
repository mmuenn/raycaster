# Input: $< Output: $@ 
CC = gcc
CFLAGS = -g -Wall
OBJECTS = raycaster-sdl.o gamelogic.o drawing.o colors.o
INCFLAGS = -I./ -I/usr/include/SDL2 -D_REENTRANT
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = -pthread -lSDL2 -lm 

all: raycaster-sdl

raycaster-sdl: $(OBJECTS)
	$(CC) -o raycaster-sdl $(OBJECTS) $(LDFLAGS) $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

.c.o :
	$(CC) -o $@ -c $(CFLAGS) $< $(INCFLAGS)
.md.pdf:
	pandoc -f pdf -i $< $@
tags:
	bash tags.sh *.c
count:
	wc *.c *.cc *.C *.cpp *.h *.hpp
clean:
	rm -f *.o

.PHONY: all
.PHONY: count
.PHONY: clean
.PHONY: tags
