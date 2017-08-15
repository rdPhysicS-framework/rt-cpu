#ifndef __COLOR_H__
#define	__COLOR_H__

#include <SDL.h>
#include <RTmath.h>

#include "..\Util\Util.h"

class Color
{
private:
	int r;
	int g;
	int b;
	int a;
	int rgb;

	void ToProcess(SDL_Surface *p_surface, int y, int x);

public:
	Color();
	Color(SDL_Surface *p_surface, int y, int x);
	Color(int r, int g, int b, int a = 0xFF);
	Color(float r, float g, float b, float a = 1.0f);
	Color(RT::Vec4f &color);

	int GetRed() const;
	int GetGreen() const;
	int GetBlue() const;
	int GetAlpha() const;
	int GetRGB() const;

	void Set(int r, int g, int b, int a);
	void Set(RT::Vec4f &color);
	void SetRed(int r);
	void SetGreen(int g);
	void SetBlue(int b);
	void GetAlpha(int a);
	void SetRGB(int rgb);

};

#endif//__COLOR_H__
