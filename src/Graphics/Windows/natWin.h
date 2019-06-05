#ifndef NATALIDE_NATWIN_H_
#define NATALIDE_NATWIN_H_

#include "globals.h"

class natWin
{
public:
	void draw (int x1, int y1, Colour c)
	{
		FATAL_ASSERT(screen_pixels);
		if ((x1 + this->x) < 0 || (x1 + this->x) > SCREEN_WIDTH || (y1 + this->y) < 0 || (y1 + this->y) > SCREEN_HEIGHT)
			return;

		Colour prev = Colour(screen_pixels[(y1 + this->y) * SCREEN_WIDTH + (x1 + this->x)]);
		float a = (float)c.a / 255;
		float ca = 1.0f - a;
		float r = (a * (float)c.r) + (ca * (float)prev.r);
		float g = (a * (float)c.g) + (ca * (float)prev.g);
		float b = (a * (float)c.b) + (ca * (float)prev.b);
		Colour now = Colour(r, g, b);

		screen_pixels[(y1 + this->y) * SCREEN_WIDTH + (x1 + this->x)] = now.getUint32();
	}

	void clear (Colour c = Colour(255, 255, 255)) 
	{
		FATAL_ASSERT(screen_pixels);
		for (int x1 = 0; x1 < width; x1++)
			for (int y1 = 0; y1 < height; y1++)
				draw(x1, y1, c);
	} 

	void fill (int x1, int y1, int x2, int y2, Colour c) 
	{
		FATAL_ASSERT(screen_pixels);
		for (int X = x1; X < x2; X++)
			for (int Y = y1; Y < y2; Y++)
				draw(X, Y, c);
	}

	void drawText (int x1, int y1, const std::string &messageText, int fontSize = 15, Colour c = Colour( 0, 0, 0 ), const std::string &fontPath = "res/Fonts/OpenSans/OpenSansRegular.ttf")
	{
		TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
		WARN_ASSERT(font);

		SDL_Color colour = { (Uint8)c.r, (Uint8)c.g, (Uint8)c.b, (Uint8)c.a };
		SDL_Surface *textSurface = TTF_RenderText_Blended(font, messageText.c_str(), colour);
		WARN_ASSERT(textSurface);

		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
		WARN_ASSERT(textTexture);

		void *pixels;
		SDL_LockTexture(textTexture, &textSurface->clip_rect, &pixels, &textSurface->pitch);
		Uint32 * uPixels = (Uint32 *) textSurface->pixels;

		for (int x2 = 0; x2 < textSurface->w; x2++)
			for (int y2 = 0; y2 < textSurface->h; y2++)
				draw(x1 + x2, y1 + y2, Colour(uPixels[(y2 * textSurface->w) + x2]));

		SDL_FreeSurface(textSurface);
	}

	virtual void event (Nat_Event *event) = 0;
	virtual void render () = 0;

	char const *sName;
	int x, y, width, height;
	Uint32 *screen_pixels;

};

#endif // NATALIDE_NATWIN_H_