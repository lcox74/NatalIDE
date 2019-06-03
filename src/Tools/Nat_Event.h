#ifndef NATALIDE_NAT_EVENT_H_
#define NATALIDE_NAT_EVENT_H_

typedef struct
{
	Nat_Event () 
	{
		x = 0; px = 0; dx = 0;
		y = 0; py = 0; dy = 0;
		mouseState = 0;
	}

	void prev ()
	{
		px = x;
		py = y;
	}

	void diff ()
	{
		dx = x - px;
		dy = y - py;
	}

	void setEvent (SDL_Event event) { e = event; }

	int x, px, dx;
	int y, py, dy;
	int mouseState;
	SDL_Event e;
} Nat_Event;

#endif // NATALIDE_NAT_EVENT_H_