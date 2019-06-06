#ifndef NATALIDE_NATWIN_H_
#define NATALIDE_NATWIN_H_

#include "globals.h"

class natWin
{
public:
	void draw (int x1, int y1, Colour c)
	{
		FATAL_ASSERT(screen_pixels);
		if ((x1 + this->x) < 0 || (x1 + this->x) > SCREEN_WIDTH || (y1 + this->y) < 0 || (y1 + this->y) > SCREEN_HEIGHT)
			return;

		Colour prev = Colour(screen_pixels[(y1 + this->y) * SCREEN_WIDTH + (x1 + this->x)]);
		float a = (float)c.a / 255;
		float ca = 1.0f - a;
		float r = (a * (float)c.r) + (ca * (float)prev.r);
		float g = (a * (float)c.g) + (ca * (float)prev.g);
		float b = (a * (float)c.b) + (ca * (float)prev.b);
		Colour now = Colour(r, g, b);

		screen_pixels[(y1 + this->y) * SCREEN_WIDTH + (x1 + this->x)] = now.getUint32();
	}

	void clear (Colour c = Colour(255, 255, 255)) 
	{
		FATAL_ASSERT(screen_pixels);
		for (int x1 = 0; x1 < width; x1++)
			for (int y1 = 0; y1 < height; y1++)
				draw(x1, y1, c);
	} 

	void fillRect (int x1, int y1, int x2, int y2, Colour c) 
	{
		FATAL_ASSERT(screen_pixels);
		for (int X = x1; X < x2; X++)
			for (int Y = y1; Y < y2; Y++)
				draw(X, Y, c);
	}

	void drawText (int x1, int y1, const std::string &messageText, int fontSize = 15, Colour c = Colour( 0xFF000000 ), const std::string &fontPath = "res/Fonts/OpenSans/OpenSansRegular.ttf")
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
				draw(x1 + x2, y1 + y2, Colour(uPixels[(y2 * textSurface->w) + x2]));

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(font);

		delete uPixels;
	}

	void drawCircle (int x1, int y1, int r, Colour c)
	{
		int x0 = 0;
		int y0 = r;
		int d = 3 - 2 * r;
		if (r <= 0) return;

		while (y0 >= x0)
		{
			draw (x1 - x0, y1 - y0, c);
            draw (x1 - y0, y1 - x0, c);
            draw (x1 + y0, y1 - x0, c);
            draw (x1 + x0, y1 - y0, c);
            draw (x1 - x0, y1 + y0, c);
            draw (x1 - y0, y1 - x0, c);
            draw (x1 + y0, y1 + x0, c);
            draw (x1 + x0, y1 + y0, c);
            if (d < 0) 
            	d += 4 * x0++ + 6;
            else 
            	d += 4 * (x0++ - y0--) + 10;
		}
	}


	void fillCircle (int x1, int y1, int r, Colour c)
	{
		int x0 = 0;
        int y0 = r;
        int d = 3 - 2 * r;
        if (r <= 0) return;

        auto drawline = [&](int sx, int ex, int ny)
        {
            for (int i = sx; i <= ex; i++)
                draw(i, ny, c);
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

	// https://www.avrfreaks.net/sites/default/files/triangles.c
    void fillTriangle (int x1, int y1, int x2, int y2, int x3, int y3, Colour c)
    {
	    auto SWAP = [](int &x, int &y) { int t = x; x = y; y = t; };
	    auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) draw (i, ny, c); };

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


	virtual void event (Nat_Event *event) = 0;
	virtual void render () = 0;

	char const *sName;
	int x, y, width, height;
	Uint32 *screen_pixels;

};

#endif // NATALIDE_NATWIN_H_