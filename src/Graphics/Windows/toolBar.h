#ifndef NATALIDE_TOOLBAR_H_
#define NATALIDE_TOOLBAR_H_

#include "globals.h"
#include "natWin.h"

class toolBar : public natWin
{
public:
	toolBar (u32 *screenPixels, char const *winName)
	{
		screen_pixels = screenPixels;
		sName = winName;
		x = 0;
		y = 0;
		width = SCREEN_WIDTH;
		height = 20;
	}
	~toolBar () { }

	void event (Nat_Event *event) override
	{
		if ((event->x >= this->x && event->x <= this->x + this->width && 
			event->y >= this->y && event->y <= this->y + this->height))
		{

		}
	}

	void render () override
	{
		clear(clearColour);
	}

	Colour clearColour = Colour(0xFFFFFFFF);
};

#endif // NATALIDE_TOOLBAR_H_