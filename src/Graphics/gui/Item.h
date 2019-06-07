#ifndef NATALIDE_ITEM_H_
#define NATALIDE_ITEM_H_

#include "globals.h"

class Item
{
public:
	void DRAW (int x, int y, Colour c)
	{
		FATAL_ASSERT(screen_pixels);
		if ((x + this->x) < 0 || (x + this->x) > SCREEN_WIDTH || (y + this->y) < 0 || (y + this->y) > SCREEN_HEIGHT)
			return;

		Colour prev = Colour(screen_pixels[(y + this->y) * SCREEN_WIDTH + (x + this->x)]);

		float a = (float)c.a / 255;
		float ca = 1.0f - a;
		float r = (a * (float)c.r) + (ca * (float)prev.r);
		float g = (a * (float)c.g) + (ca * (float)prev.g);
		float b = (a * (float)c.b) + (ca * (float)prev.b);

		Colour now = Colour(r, g, b);

		screen_pixels[(y + this->y) * SCREEN_WIDTH + (x + this->x)] = now.getUint32();

	}


	void fillRect (int x1, int y1, int w, int h, Colour c) 
	{
		for (int x2 = 0; x2 < w; x2++)
			for (int y2 = 0; y2 < h; y2++)
				DRAW(x1 + x2, y1 + y2, c);
	}

	void drawText (int x1, int y1, const std::string &messageText, int fontSize = 15, int alignment = 0, Colour c = Colour( 0xFF000000 ), const std::string &fontPath = "res/Fonts/OpenSans/OpenSansRegular.ttf")
	{
		TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
		WARN_ASSERT_MESS(font, TTF_GetError());

		SDL_Color colour = { (Uint8)c.r, (Uint8)c.g, (Uint8)c.b, (Uint8)c.a };
		SDL_Surface *textSurface = TTF_RenderText_Blended(font, messageText.c_str(), colour);
		WARN_ASSERT(textSurface);

		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
		WARN_ASSERT(textTexture);

		void *pixels;
		SDL_LockTexture(textTexture, &textSurface->clip_rect, &pixels, &textSurface->pitch);
		Uint32 * uPixels = (Uint32 *) textSurface->pixels;

		switch (alignment)
		{
			// Top
			case 0: // Left
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW(x1 + x2, y1 + y2, Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
			case 1: // Centered
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW((x1 + x2) - (int)((float)textSurface->w / 2.0f), y1 + y2, Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
			case 2: // Right
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW(x1 + x2 - textSurface->w, y1 + y2, Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
			// Middle
			case 3: // Left
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW(x1 + x2, y1 + y2 - (int)((float)textSurface->h / 2.0f), Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
			case 4: // Centered
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW((x1 + x2) - (int)((float)textSurface->w / 2.0f), y1 + y2 - (int)((float)textSurface->h / 2.0f), Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
			case 5: // Right
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW(x1 + x2 - textSurface->w, y1 + y2 - (int)((float)textSurface->h / 2.0f), Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
			// Bottom
			case 6: // Left
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW(x1 + x2, y1 + y2 - textSurface->h, Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
			case 7: // Centered
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW((x1 + x2) - (int)((float)textSurface->w / 2.0f), y1 + y2 - textSurface->h, Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
			case 8: // Right
				for (int x2 = 0; x2 < textSurface->w; x2++)
					for (int y2 = 0; y2 < textSurface->h; y2++)
						DRAW(x1 + x2 - textSurface->w, y1 + y2 - textSurface->h, Colour(uPixels[(y2 * textSurface->w) + x2]));
				break;
		}

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(font);

		delete uPixels;
	}

	virtual void Event (Nat_Event *event) = 0;
	virtual void Render () = 0;

	int x, y, width, height;
	Uint32 *screen_pixels = nullptr;
};

#endif // NATALIDE_ITEM_H_