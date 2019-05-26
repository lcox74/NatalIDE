#ifndef NATALIDE_PROJECTVIEW_H_
#define NATALIDE_PROJECTVIEW_H_

#include "globals.h"
#include "natWin.h"

class projectView : public natWin
{
public:
	projectView (Uint32 *screenPixels, char* winName, int x1 = 100, int y1 = 100, int w = 100, int h = 100)
				: sName(winName), x(x1), y(y1), width(w), height(h)
	{

	}

	void render () 
	{
		clear(255);
	}
	
};

#define //NATALIDE_PROJECTVIEW_H_