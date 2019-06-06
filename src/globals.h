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

#ifndef NATALIDE_ASSERTS_
#define NATALIDE_ASSERTS_
	#include "Tools/Nat_Assert.h"
#endif // NATALIDE_ASSERTS_

#include "Tools/Nat_Event.h"

#include "Graphics/Colour.h"
#include "Graphics/Text.h"

#ifndef NATALIDE_RENDERER_
#define NATALIDE_RENDERER_
	static SDL_Renderer *ren;
#endif // NATALIDE_RENDERER_