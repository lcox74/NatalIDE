#include "globals.h"

#include "natWin.h"

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
	
	SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
	SDL_Texture *screen = SDL_CreateTexture(ren, format->format, 
											SDL_TEXTUREACCESS_STREAMING, 
											SCREEN_WIDTH, SCREEN_HEIGHT);
	assert(screen);

	u32 *screen_pixels = (u32*) calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(u32));
	assert(screen_pixels);

	natWin projView = natWin(screen_pixels, "Proj");

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

		projView.clear(SDL_MapRGB(format, 255, 255, 255));

		SDL_UpdateTexture(screen, NULL, screen_pixels, SCREEN_WIDTH * sizeof(u32));
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, screen, NULL, NULL);
		SDL_RenderPresent(ren);
	}

	return 1;
}