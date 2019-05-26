#ifndef NATALIDE_NATWIN_H_
#define NATALIDE_NATWIN_H_

#include "globals.h"

class natWin
{
public:
	natWin(Uint32 *screenPixels, char const *winName, int x1 = 100, int y1 = 100, int w = 100, int h = 100)
			: screen_pixels(screenPixels), sName(winName), x(x1), y(y1), width(w), height(h) { }
	~natWin() {}

	void draw (int x1, int y1, Uint32 colour)
	{
		assert(screen_pixels);
		if (x1 < 0 || x1 + width > SCREEN_WIDTH || y1 < 0 || y1 + height > SCREEN_HEIGHT)
			return;
		screen_pixels[y1 * SCREEN_WIDTH + x1] = colour;
	}

	void clear (Uint32 colour = 0) 
	{
		assert(screen_pixels);
		for (int x1 = 0; x1 < width; x1++)
			for (int y1 = 0; y1 < height; y1++)
				draw(x1 + x, y1 + y, colour);
	} 

	char const *sName;
	int x, y, width, height;
	Uint32 *screen_pixels;
};

#endif // NATALIDE_NATWIN_H_