#ifndef NATALIDE_TEXT_H_
#define NATALIDE_TEXT_H_

#include "globals.h"

class Text {
public:
	Text (const std::string &fontPath, int fontSize, const std::string &messageText, Colour c)
	{
		tTextTexture = loadFont(fontPath, fontSize, messageText, c);
		SDL_QueryTexture(tTextTexture, nullptr, nullptr, &rTextRect.w, &rTextRect.h);
	}

	void display(int x, int y)
	{
		rTextRect.x = x;
		rTextRect.y = y;
		SDL_RenderCopy(ren, tTextTexture, nullptr, &rTextRect);
	}

	SDL_Texture *loadFont(const std::string &fontPath, int fontSize, const std::string &messageText, Colour c)
	{
		TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
		WARN_ASSERT(font);

		SDL_Color colour = { (Uint8)c.r, (Uint8)c.g, (Uint8)c.b, (Uint8)c.a };
		printf("%d\n", colour.r);

		SDL_Surface *textSurface = TTF_RenderText_Solid(font, messageText.c_str(), colour);
		WARN_ASSERT(textSurface);

		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
		WARN_ASSERT(textTexture);
 
		SDL_FreeSurface(textSurface);
		return textTexture;
	}

private:
	SDL_Texture *tTextTexture = nullptr;
	mutable SDL_Rect rTextRect;
};

#endif // NATALIDE_TEXT_H_