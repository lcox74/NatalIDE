#ifndef NATALIDE_COLOUR_H_
#define NATALIDE_COLOUR_H_

class Colour
{
public:
	Colour(int R, int G, int B, int A = 255)
		: r(R), g(G), b(B) { }

	Colour(u32 hex) 
	{
		a = (hex & 0xFF000000) >> 24;
		r = (hex & 0x00FF0000) >> 16;
		g = (hex & 0x0000FF00) >> 8;
		b = (hex & 0x000000FF) >> 0;
	}
	~Colour() { }

	u32 getUint32 () 
	{
		u32 temp = (a << 24) + (r << 16) + (g << 8) + (b << 0);
		return temp;
	}

	int r, g, b, a;
};
#endif // NATALIDE_COLOUR_H_