#include <SDL2/SDL.h>
#include "colors.h"
const color blue  = {.b=0xFF};
const color green = {.g=0xFF};
const color red   = {.r=0xFF};
const color dgrey = {.r=0x18, .g=0x18, .b=0x18};
const color lgrey = {.r=0xAA, .g=0xAA, .b=0xAA};

Uint32 color_to_Uint32(color clr){
	return * (Uint32 * ) &clr;
}

