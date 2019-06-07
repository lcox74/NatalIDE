#ifndef NATALIDE_NATWIN_H_
#define NATALIDE_NATWIN_H_

#include "globals.h"

class natWin
{
public:
	void draw (int x1, int y1, Colour c)
	{
		DRAW(screen_pixels, x1 + this->x, y1 + this->y, c);
	}

	void clear (Colour c = Colour(255, 255, 255)) 
	{
		FATAL_ASSERT(screen_pixels);
		for (int x1 = 0; x1 < width; x1++)
			for (int y1 = 0; y1 < height; y1++)
				draw(x1, y1, c);
	} 

	void drawRect (int x1, int y1, int x2, int y2, Colour c) 
	{
		DRAWRECT(screen_pixels, x1 + this->x, y1 + this->y, x2 + this->x, y2 + this->y, c);
	}

	void fillRect (int x1, int y1, int x2, int y2, Colour c) 
	{
		FILLRECT(screen_pixels, x1 + this->x, y1 + this->y, x2 + this->x, y2 + this->y, c);
	}

	void drawText (int x1, int y1, const std::string &messageText, int fontSize = 15, Colour c = Colour( 0xFF000000 ), const std::string &fontPath = "res/Fonts/OpenSans/OpenSansRegular.ttf")
	{
		DRAWTEXT(screen_pixels, x1 + this->x, y1 + this->y, messageText, fontSize, c, fontPath);
	}

	void drawCircle (int x1, int y1, int r, Colour c)
	{
		DRAWCIRCLE(screen_pixels, x1 + this->x, y1 + this->y, r, c);	
	}

	void fillCircle (int x1, int y1, int r, Colour c)
	{
		FILLCIRCLE(screen_pixels, x1 + this->x, y1 + this->y, r, c);
	}

    void fillTriangle (int x1, int y1, int x2, int y2, int x3, int y3, Colour c)
    {
	    FILLTRIANGLE(screen_pixels, x1 + this->x, y1 + this->y, x2 + this->x, y2 + this->y,  + this->x, y3 + this->y, c);
    }

    void drawTriangle (int x1, int y1, int x2, int y2, int x3, int y3, Colour c)
    {
	    DRAWTRIANGLE(screen_pixels, x1 + this->x, y1 + this->y, x2 + this->x, y2 + this->y, x3 + this->x, y3 + this->y, c);
    }

	virtual void event (Nat_Event *event) = 0;
	virtual void render () = 0;

	char const *sName;
	int x, y, width, height;
	Uint32 *screen_pixels = nullptr;

};

#endif // NATALIDE_NATWIN_H_