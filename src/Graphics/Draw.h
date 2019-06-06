#ifndef NATALIDE_DRAW_H_
#define NATALIDE_DRAW_H_

#include "globals.h"

void DRAW (Uint32 *screen, int x, int y, Colour c)
{
	FATAL_ASSERT(screen);
	if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
		return;

	Colour prev = Colour(screen[y * SCREEN_WIDTH + x]);
	float a = (float)c.a / 255;
	float ca = 1.0f - a;
	float r = (a * (float)c.r) + (ca * (float)prev.r);
	float g = (a * (float)c.g) + (ca * (float)prev.g);
	float b = (a * (float)c.b) + (ca * (float)prev.b);
	Colour now = Colour(r, g, b);

	screen[y * SCREEN_WIDTH + x] = now.getUint32();
}

void DRAWLINE (Uint32 *screen, int x1, int y1, int x2, int y2, Colour c)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;

    // Straight Lines idea by Gurkanctn
    if (dx == 0) // Line is Vertical
    {
        if (y2 < y1) std::swap(y1, y2);
        for (y = y1; y <= y2; y++)
            DRAW(screen, x1, y, c);
        return;
    }
    if (dy == 0) // Line is Horizontal
    {
        if (x2 < x1) std::swap(x1, x2);
        for (x = x1; x <= x2; x++)
            DRAW(screen, x, y1, c);
        return;
    }

    // Line is not Straight
    dx1 = abs(dx); dy1 = abs(dy);
    px = 2 * dy1 - dx1; py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0) { x = x1; y = y1; xe = x2; }
        else { x = x2; y = y2; xe = x1; }
        DRAW(screen, x, y, c);

        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0) px = px + 2 * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            DRAW(screen, x, y, c);
        }
    }
    else
    {
        if (dx >= 0) { x = x1; y = y1; ye = y2; }
        else { x = x2; y = y2; ye = y1; }
       	DRAW(screen, x, y, c);

        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py < 0) py = py + 2 * dx1;
            else
            {
	            if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
	            py = py + 2 * (dx1 - dy1);
            }
            DRAW(screen, x, y, c);
        }
    }

}

void DRAWRECT (Uint32 *screen, int x, int y, int w, int h, Colour c)
{
	DRAWLINE(screen, x    , y    , x + w, y    , c);
	DRAWLINE(screen, x    , y + h, x + w, y + h, c);
	DRAWLINE(screen, x    , y    , x    , y    , c);
	DRAWLINE(screen, x + w, y    , x + w, y + h, c);
}
void FILLRECT (Uint32 *screen, int x, int y, int w, int h, Colour c)
{
	for (int x1 = 0; x1 < w; x1++)
		for (int y1 = 0; y1 < h; y1++)
			DRAW(screen, x + x1, y + y1, c);
}

void DRAWTRIANGLE (Uint32 *screen, int x, int y, int x1, int y1, int x2, int y2, Colour c)
{
	DRAWLINE(screen, x, y, x1, y1, c);
	DRAWLINE(screen, x, y, x2, y2, c);
	DRAWLINE(screen, x1, y1, x2, y2, c);
}
// https://www.avrfreaks.net/sites/default/files/triangles.c
void FILLTRIANGLE (Uint32 *screen, int x1, int y1, int x2, int y2, int x3, int y3, Colour c)
{
    auto SWAP = [](int &x, int &y) { int t = x; x = y; y = t; };
    auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) DRAW (screen, i, ny, c); };

    int t1x, t2x, y, minx, maxx, t1xp, t2xp;
    bool changed1 = false, changed2 = false;
    int signx1, signx2, dx1, dy1, dx2, dy2;
    int e1, e2;

    // Sort Vertices
    if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }
    if (y1 > y3) { SWAP(y1, y3); SWAP(x1, x3); }
    if (y2 > y3) { SWAP(y2, y3); SWAP(x2, x3); }

    t1x = t2x = x1; y = y1; // Starting Points
    dx1 = (int)(x2 - x1);
    if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
    else signx1 = 1;
    dy1 = (int)(y2 - y1);

    dx2 = (int)(x3 - x1);
    if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
    else signx2 = 1;
    dy2 = (int)(y3 - y1);

    if (dy1 > dx1) { SWAP(dx1, dy1); changed1 = true; }
    if (dy2 > dx2) { SWAP(dy2, dx2); changed2 = true; }

    e2 = (int)(dx2 >> 1);

    if (y1 == y2) goto next; // If the top of the triangle is flat then goto next
    e1 = (int)(dx1 >> 1);

    for (int i = 0; i < dx1;)
    {
        t1xp = 0; t2xp = 0;
        if (t1x < t2x) { minx = t1x; maxx = t2x; }
        else { minx = t2x; maxx = t1x; }

        while (i < dx1)
        {
            i++;
            e1 += dy1;
            while (e1 >= dx1)
            {
                e1 -= dx1;
                if (changed1) t1xp = signx1;
                else goto next1;
            }
            if (changed1) break;
            else t1x += signx1;
        }

next1:
        while (1)
        {
            e2 += dy2;
            while (e2 >= dx2)
            {
                e2 -= dx2;
                if (changed2) t2xp = signx2;
                else goto next2;
            }
            if (changed2) break;
            else t2x += signx2;
        }
next2:
        if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
        if (maxx < t2x) maxx = t1x; if (maxx < t2x) maxx = t2x;
        drawline(minx, maxx, y);

        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y == y2) break;
	}

next:
	dx1 = (int)(x3 - x2);
	if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
	else signx1 = 1;
	dy1 = (int)(y3 - y2);
	t1x = x2;

	if (dy1 > dx1) { SWAP(dy1, dx1); changed1 = true; }
	else changed1 = false;

	e1 = (int)(dx1 >> 1);

	for (int i = 0; i <= dx1; i++)
	{
        t1xp = 0; t2xp = 0;
        if (t1x < t2x) { minx = t1x; maxx = t2x; }
        else { minx = t2x; maxx = t1x; }

        // Process first line until y value is about to change
        while (i < dx1)
        {
            e1 += dy1;
            while (e1 >= dx1)
            {
                e1 -= dx1;
                if (changed1) { t1xp = signx1; break; }
                else goto next3;
            }
            if (changed1) break;
            else t1x += signx1;
            if (i < dx1) i++;
        }
next3:
        // Process second line untill y value is about to change
        while (t2x != x3)
        {
            e2 += dy2;
            while (e2 >= dx2)
            {
                e2 -= dx2;
                if (changed2) t2xp = signx2;
                else goto next4;
            }
            if (changed2) break;
            else t2x += signx2;
        }
next4:
        if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
        if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
        drawline(minx, maxx, y);
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y > y3) return;
    }
}

void DRAWCIRCLE (Uint32 *screen, int x1, int y1, int r, Colour c)
{
	int x0 = 0;
	int y0 = r;
	int d = 3 - 2 * r;
	if (r <= 0) return;

	while (y0 >= x0)
	{
		DRAW (screen, x1 - x0, y1 - y0, c);
        DRAW (screen, x1 - y0, y1 - x0, c);
        DRAW (screen, x1 + y0, y1 - x0, c);
        DRAW (screen, x1 + x0, y1 - y0, c);
        DRAW (screen, x1 - x0, y1 + y0, c);
        DRAW (screen, x1 - y0, y1 - x0, c);
        DRAW (screen, x1 + y0, y1 + x0, c);
        DRAW (screen, x1 + x0, y1 + y0, c);
        if (d < 0) 
        	d += 4 * x0++ + 6;
        else 
        	d += 4 * (x0++ - y0--) + 10;
	}
}

void FILLCIRCLE (Uint32 *screen, int x1, int y1, int r, Colour c)
{
	int x0 = 0;
    int y0 = r;
    int d = 3 - 2 * r;
    if (r <= 0) return;

    auto drawline = [&](int sx, int ex, int ny)
    {
        for (int i = sx; i <= ex; i++)
            DRAW(screen, i, ny, c);
    };

    while (y0 >= x0)
    {
        drawline (x1 - x0, x1 + x0, y1 - y0);
        drawline (x1 - y0, x1 + y0, y1 - x0);
        drawline (x1 - x0, x1 + x0, y1 + y0);
        drawline (x1 - y0, x1 + y0, y1 + x0);
        if (d < 0) 
        	d += 4 * x0++ +6;
        else 
        	d += 4 * (x0++ - y0--) + 10;
    }
}

void DRAWTEXT (Uint32 *screen, int x1, int y1, const std::string &messageText, int fontSize = 15, Colour c = Colour( 0xFF000000 ), const std::string &fontPath = "res/Fonts/OpenSans/OpenSansRegular.ttf")
	{
		TTF_Font *font = TTF_OpenFont(fontPath.c_str(), fontSize);
		WARN_ASSERT_MESS(font, TTF_GetError());

		SDL_Color colour = { (Uint8)c.r, (Uint8)c.g, (Uint8)c.b, (Uint8)c.a };
		SDL_Surface *textSurface = TTF_RenderText_Blended(font, messageText.c_str(), colour);
		WARN_ASSERT(textSurface);

		SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
		WARN_ASSERT(textTexture);

		void *pixels;
		SDL_LockTexture(textTexture, &textSurface->clip_rect, &pixels, &textSurface->pitch);
		Uint32 * uPixels = (Uint32 *) textSurface->pixels;

		for (int x2 = 0; x2 < textSurface->w; x2++)
			for (int y2 = 0; y2 < textSurface->h; y2++)
				DRAW(screen, x1 + x2, y1 + y2, Colour(uPixels[(y2 * textSurface->w) + x2]));

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(font);

		delete uPixels;
	}

#endif // NATALIDE_DRAW_H_