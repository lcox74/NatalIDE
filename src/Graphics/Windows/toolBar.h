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

		toolBtns.push_back(Button(screenPixels, "File", 0, 0, 40, 20));
		toolBtns.push_back(Button(screenPixels, "Edit", 40, 0, 40, 20));
		toolBtns.push_back(Button(screenPixels, "Selection", 80, 0, 70, 20));
		toolBtns.push_back(Button(screenPixels, "Find", 150, 0, 40, 20));
		toolBtns.push_back(Button(screenPixels, "View", 190, 0, 45, 20));
		toolBtns.push_back(Button(screenPixels, "Tools", 235, 0, 50, 20));
	}
	~toolBar () 
	{ 
		toolBtns.clear();
		toolBtns.resize(0);
	}

	void event (Nat_Event *event) override
	{
		if ((event->x >= this->x && event->x <= this->x + this->width && event->y >= this->y && event->y <= this->y + this->height))
			for (Button &btn : toolBtns)
				btn.Event(event);
	}

	void render () override
	{
		clear(clearColour);
		for (Button &btn : toolBtns)
			btn.Render();
	}

	Colour clearColour = Colour(0xFFFFFFFF);
	std::vector<Button> toolBtns;
};

#endif // NATALIDE_TOOLBAR_H_