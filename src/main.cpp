#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "SDL2/SDL.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

typedef Uint32 u32;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *win =SDL_CreateWindow("NatalIDE", 
									   SDL_WINDOWPOS_UNDEFINED, 
									   SDL_WINDOWPOS_UNDEFINED, 
									   SCREEN_WIDTH, SCREEN_HEIGHT, 
									   0); // Flags (Fullscreen here)
	assert(win);

	SDL_Renderer *ren = SDL_CreateRenderer(win, 
										   0, 
										   SDL_RENDERER_SOFTWARE);
	assert(ren);
	
	SDL_Texture *screen = SDL_CreateTexture(ren, 
											SDL_PIXELFORMAT_RGB888, 
											SDL_TEXTUREACCESS_STREAMING, 
											SCREEN_WIDTH, SCREEN_HEIGHT);
	assert(screen);

	u32 *screen_pixels = (u32*) calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(u32));
	assert(screen_pixels);

	bool running = true;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) 
			{
				running = false;
				break;
			}
		}

		SDL_UpdateTexture(screen, NULL, screen_pixels, SCREEN_WIDTH * sizeof(u32));
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, screen, NULL, NULL);
		SDL_RenderPresent(ren);
	}

	return 1;
}