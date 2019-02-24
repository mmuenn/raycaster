// colors.h
#include <SDL2/SDL.h>
typedef struct {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char x;
} color;
Uint32 color_to_Uint32(color clr);

