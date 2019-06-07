#ifndef NATALIDE_ITEM_BUTTON_H_
#define NATALIDE_ITEM_BUTTON_H_

#include "globals.h"
#include "Item.h"

class Button : public Item
{
public:
	Button() 
	{
		this->x = 0;
		this->y = 0;
		this->width = 40; 
		this->height = 20;

		this->btnText = "Button";

		this->normal = Colour(0xFFFFFFFF);
		this->currentColour = Colour(0xFFFFFFFF);
		this->hover = Colour(0xFFE5F3FF);
		this->click = Colour(0xFFCCE8FF);
	}
	Button(Uint32 *screenPixels, char const *text, int x1, int y1, int w1, int h1, Colour nColour = Colour(0xFFFFFFFF), Colour hColour = Colour(0xFFE5F3FF), Colour cColour = Colour(0xFFCCE8FF)) 
	{
		this->x = x1;
		this->y = y1;
		this->width = w1;
		this->height = h1;

		this->btnText = text;

		this->normal = nColour;
		this->currentColour = nColour;
		this->hover = hColour;
		this->click = cColour;

		this->screen_pixels = screenPixels;
	}
	~Button() { }

	void Event (Nat_Event *event)
	{	 
		if ((event->x >= this->x && event->x <= this->x + this->width && 
			event->y >= this->y && event->y <= this->y + this->height))
			currentColour = (event->mouseState >= 1) ? click : hover;
		else
			currentColour = normal;
	}
	void Render ()
	{
		fillRect (0, 0, width, height, currentColour);
		drawText ((int)(width / 2), (int)(height / 2), btnText, 13, MIDDLE_CENTER_ANCHOR);
	}

	char const *btnText;

	Colour currentColour;
	Colour normal;
	Colour hover;
	Colour click;
};

#endif // NATALIDE_ITEM_BUTTON_H_