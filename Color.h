#pragma once
struct Color 
{
	Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	Color(unsigned char red, unsigned char green, unsigned char blue)
	{
		r = red;
		g = green;
		b = blue;
		a = 255;
	}

	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

