#include <SDL2/SDL.h>
#include "colors.h"
#include "drawing.h"
#include "defines.h"

int get_line_height(float d){
	const float tana = tan(FOV / 2.0f);
	int h;
	float df = (float) d;	
	float hf =  tana / (df/64.0) * HEIGHT * 2;
	// printf("hf: %f, tana: %f\ndf: %f d %d\n", hf, tana, df,d);
	h = floor(hf);
	if (hf > HEIGHT) return HEIGHT;;
	return h;
}
void set_pixel(SDL_Surface *surface, int x, int y, color clr)
{

  color *target_pixel = (color *) surface->pixels + y * WIDTH + x;
  *target_pixel = clr;
}

void draw_centered_vline(SDL_Surface *surface, int x, int h, color clr){
	int y1, y2;
	y1 = HEIGHT / 2 - h / 2;
	y2 = HEIGHT / 2 + h / 2;
	for (int y = y1; y<y2; y++){
		set_pixel(surface, x, y, clr);
	}
}
