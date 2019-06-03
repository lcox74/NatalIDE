#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>

#ifdef _WIN32
	#include <iostream>
	#include <windows.h>
#endif

#include "SDL2/SDL.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

typedef Uint32 u32;

#include "Tools/Nat_Assert.h"
#include "Tools/Nat_Event.h"

#include "Graphics/Colour.h"
