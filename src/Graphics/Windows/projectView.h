#ifndef NATALIDE_PROJECTVIEW_H_
#define NATALIDE_PROJECTVIEW_H_

#include "globals.h"
#include "natWin.h"

class projectView : public natWin
{
public:
	projectView (Uint32 *screenPixels, char const *winName, int x1 = 0, int y1 = 0, int w = 100, int h = 100)
	{
		screen_pixels = screenPixels;
		sName = winName;
		x = x1;
		y = (y1 < 20) ? 20 : y1;
		width = (w > SCREEN_WIDTH) ? SCREEN_WIDTH : w;
		height = (h > SCREEN_HEIGHT) ? h - 20 : h;
	}
	~projectView () { }

	void event (Nat_Event *event) override
	{
		if ((event->x >= this->x && event->x <= this->x + this->width && 
			event->y >= this->y && event->y <= this->y + this->height) || dragging)
		{
			if (event->mouseState == 1)
			{
				clickX = event->x - this->x;
				clickY = event->y - this->y;
				dragging = true;
			}
			else if (event->mouseState == 2)
			{
				this->x = event->x - clickX;
				this->y = event->y - clickY;
			}
			else
				dragging = false;
		}
	}

	void render () override
	{
		y = (y < 20) ? 20 : y;
		clear(clearColour);
	}

	Colour clearColour = Colour(0xFF444444);
	bool dragging = false;
	int clickX, clickY;
};

#endif //NATALIDE_PROJECTVIEW_H_