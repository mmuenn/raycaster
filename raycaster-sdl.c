#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include "defines.h"
#include "colors.h"
#include "gamelogic.h"
#include "drawing.h"
#include <time.h>
// Get extern definitions for colors
extern const color red, green, blue, dgrey, lgrey;
// Get cam
cam player_cam;
// Function for rendering
void render(SDL_Surface * surface){
	int dist;
	float left_angle;
	float fov = TO_RAD( FOV );
	cam temp_cam;
	vec2 intersection;
	temp_cam.position = player_cam.position;
	temp_cam.angle = player_cam.angle;
	SDL_LockSurface(surface);
	SDL_FillRect(surface, NULL, color_to_Uint32(dgrey));
	left_angle = player_cam.angle - fov / 2;
	for (int x = 0; x < WIDTH; x++){
		temp_cam.angle = left_angle + x / ((float) WIDTH) * fov; 
		intersection = get_ray_intersection(temp_cam);
		dist = distance(temp_cam.position, intersection);
		if (!(floor(intersection.x) == 0 && floor(intersection.y) ==0)){
			draw_centered_vline(surface, x, get_line_height(dist), red);
		}
	}
	SDL_UnlockSurface(surface);
}
int main(){
	
	player_cam.angle = 0.f;
	player_cam.position.x = 600;
   	player_cam.position.y = 120;
    SDL_Window *window;        				// Declare window pointer
	SDL_Surface *window_surface;			// Declare surface pointer
	SDL_Init(SDL_INIT_VIDEO);   	  		// Initialize SDL2
	float dx;
	init_logic();	
	// Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Raycaster",                  	// Window title
        SDL_WINDOWPOS_UNDEFINED,           	// Initial x position
        SDL_WINDOWPOS_UNDEFINED,           	// Initial y position
        WIDTH,                              // Width, in pixels
        HEIGHT,                             // Height, in pixels
        0                					// Flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
	SDL_Event e;
	char quit = 0;
	// Get Surface from window
	window_surface = SDL_GetWindowSurface(window);
   	// Enable RLE
	SDL_SetSurfaceRLE(window_surface, 1);
	//SDL_SetWindowInputFocus(window);	
	SDL_RaiseWindow(window);
	if (SDL_CaptureMouse(1)==-1){
		printf("Mouse capture not supported. %s\n", SDL_GetError());
	};
	if (SDL_SetRelativeMouseMode(1)==-1){
		printf("Relative mouse mode not supported. %s\n", SDL_GetError());
	}
	// The window is open: could enter program loop here (see SDL_PollEvent())
	while(!quit){
		while(SDL_PollEvent( &e ) != 0){
			if (e.type == SDL_QUIT) quit = 1;
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
					case SDLK_DOWN:
						move_vec(&player_cam.position, player_cam.angle, -10);
						break;
					case SDLK_UP:
						move_vec(&player_cam.position, player_cam.angle, 10);
						break;
					case SDLK_RIGHT:
						player_cam.angle+=0.7;
						break;
					case SDLK_LEFT:
						player_cam.angle-=0.7;
						break;
					case SDLK_ESCAPE:
						quit = 1;
						break;
				}
			if (e.type == SDL_MOUSEMOTION)
			{
				printf("MOUSEMOTION\n");
				dx = e.motion.xrel;
				printf("%f\n", dx);
				player_cam.angle += dx;
				// cout << "Mouse = (" << deltaX << ", " << deltaY << ")" << endl;
			}
			}
		}
		render(window_surface);
		// Update window after we have drawn to the surface
		SDL_UpdateWindowSurface(window);

	}	

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}

