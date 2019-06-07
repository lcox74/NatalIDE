#ifndef NATALIDE_TOOLBAR_H_
#define NATALIDE_TOOLBAR_H_

#include "globals.h"
#include "natWin.h"

class toolBar : public natWin
{
public:
	toolBar (Uint32 *screenPixels, char const *winName)
	{
		screen_pixels = screenPixels;
		sName = winName;
		x = 0;
		y = 0;
		width = SCREEN_WIDTH;
		height = 20;

		fileBtn = Button(screenPixels, "File", 0, 0, 40, 20);
		editBtn = Button(screenPixels, "Edit", 40, 0, 40, 20);
		selBtn = Button(screenPixels, "Selection", 80, 0, 70, 20);
		findBtn = Button(screenPixels, "Find", 150, 0, 40, 20);
		viewBtn = Button(screenPixels, "View", 190, 0, 45, 20);
		toolBtn = Button(screenPixels, "Tools", 235, 0, 50, 20);
	}
	~toolBar () { }

	void event (Nat_Event *event) override
	{
		if ((event->x >= this->x && event->x <= this->x + this->width && 
			event->y >= this->y && event->y <= this->y + this->height))
		{

		}

		fileBtn.Event(event);
		editBtn.Event(event);
		selBtn.Event(event);
		findBtn.Event(event);
		viewBtn.Event(event);
		toolBtn.Event(event);
	}

	void render () override
	{
		clear(clearColour);
		fileBtn.Render();
		editBtn.Render();
		selBtn.Render();
		findBtn.Render();
		viewBtn.Render();
		toolBtn.Render();

		// drawText(7, 1, "File", 13);
		// drawText(40, 1, "Edit", 13);
		// drawText(75, 1, "Selection", 13);
		// drawText(143, 1, "Find", 13);
		// drawText(185, 1, "View", 13);
		// drawText(225, 1, "Tools", 13);
	}

	Colour clearColour = Colour(0xFFFFFFFF);
	Button fileBtn, editBtn, selBtn, findBtn, viewBtn, toolBtn;
};

#endif // NATALIDE_TOOLBAR_H_