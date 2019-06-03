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
		screen_pixels[(y1 + this->y) * SCREEN_WIDTH + (x1 + this->x)] = c.getUint32();
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

	virtual void event (Nat_Event *event) = 0;
	virtual void render () = 0;

	char const *sName;
	int x, y, width, height;
	u32 *screen_pixels;
};

#endif // NATALIDE_NATWIN_H_