#include "globals.h"

#include "Graphics/Windows/subWindows.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *win =SDL_CreateWindow("NatalIDE", 
									   SDL_WINDOWPOS_UNDEFINED, 
									   SDL_WINDOWPOS_UNDEFINED, 
									   SCREEN_WIDTH, SCREEN_HEIGHT, 
									   0); // Flags (Fullscreen here)
	FATAL_ASSERT(win);

	SDL_Renderer *ren = SDL_CreateRenderer(win, 
										   0, 
										   SDL_RENDERER_SOFTWARE);
	FATAL_ASSERT(ren);
	
	SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);
	SDL_Texture *screen = SDL_CreateTexture(ren, format->format, 
											SDL_TEXTUREACCESS_STREAMING, 
											SCREEN_WIDTH, SCREEN_HEIGHT);
	FATAL_ASSERT(screen);

	u32 *screen_pixels = (u32*) calloc(SCREEN_WIDTH * SCREEN_HEIGHT, sizeof(u32));
	FATAL_ASSERT(screen_pixels);

	std::vector<natWin*> subWins;
	subWins.push_back(new projectView(screen_pixels, "ProjectView"));
	subWins.push_back(new toolBar(screen_pixels, "ToolBar"));

	Nat_Event *Nat_event = new Nat_Event();
	int temp = 0;
	bool running = true;
	while (running)
	{
		SDL_Event event;

		if (Nat_event->mouseState == -1)
			Nat_event->mouseState = 0;
		if (Nat_event->mouseState == 1)
			Nat_event->mouseState = 2;

		Nat_event->prev();
		
		while (SDL_PollEvent(&event))
		{
			Nat_event->setEvent(event);

			if (event.type == SDL_MOUSEMOTION)
				SDL_GetMouseState( &Nat_event->x, &Nat_event->y );
			else if (event.type == SDL_MOUSEBUTTONDOWN)
				Nat_event->mouseState = (Nat_event->mouseState == 1) ? 2 : 1;
			else if (event.type == SDL_MOUSEBUTTONUP)
				Nat_event->mouseState = -1;
			else if (event.type == SDL_QUIT) 
			{
				running = false;
				break;
			}

			for ( auto w: subWins )
				w->event(Nat_event);
		}
		Nat_event->diff();

		// Clear screen
		Colour clearColour = Colour(20, 20, 20);
		for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
			screen_pixels[i] = clearColour.getUint32();

		// Render Sub Windows
		for ( auto w: subWins )
			w->render();

		SDL_UpdateTexture(screen, NULL, screen_pixels, SCREEN_WIDTH * sizeof(u32));
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, screen, NULL, NULL);
		SDL_RenderPresent(ren);
	}

	return 1;
}