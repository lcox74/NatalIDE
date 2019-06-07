#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

#ifdef _WIN32
	#include <iostream>
	#include <windows.h>
#else
	#error Need to make Unix capatable
#endif

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

#define TOP_LEFT_ANCHOR 0
#define TOP_CENTER_ANCHOR 1
#define TOP_RIGHT_ANCHOR 2
#define MIDDLE_LEFT_ANCHOR 3
#define MIDDLE_CENTER_ANCHOR 4
#define MIDDLE_RIGHT_ANCHOR 5
#define BOTTOM_LEFT_ANCHOR 6
#define BOTTOM_CENTER_ANCHOR 7
#define BOTTOM_RIGHT_ANCHOR 8

#ifndef NATALIDE_ASSERTS_
#define NATALIDE_ASSERTS_
	#include "Tools/Nat_Assert.h"
#endif // NATALIDE_ASSERTS_

#include "Tools/Nat_Event.h"

#include "Graphics/Colour.h"
#include "Graphics/Draw.h"

#include "Graphics/gui/Button.h"

#ifndef NATALIDE_RENDERER_
#define NATALIDE_RENDERER_
	static SDL_Renderer *ren;
#endif // NATALIDE_RENDERER_