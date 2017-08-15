#include "Color.h"

void Color::ToProcess(SDL_Surface *p_surface, int y, int x)
{
	Uint32 *pixel = (Uint32 *)p_surface->pixels + (y * p_surface->pitch / 4) + x;

	r = ((*pixel) & p_surface->format->Rmask) >> p_surface->format->Rshift;
	g = ((*pixel) & p_surface->format->Gmask) >> p_surface->format->Gshift;
	b = ((*pixel) & p_surface->format->Bmask) >> p_surface->format->Bshift;
	rgb = (*pixel);
}

Color::Color() :
	r(0), g(0), b(0), a(0), rgb(0)
{}

Color::Color(SDL_Surface *p_surface, int y, int x)
{
	ToProcess(p_surface, y, x);
}

Color::Color(int r, int g, int b, int a) :
	r(r), g(g), b(b), a(a), rgb(((r & 0xFF) << RSHIFT) |
								((g & 0xFF) << GSHIFT) |
								((b & 0xFF) << BSHIFT) |
								((a & 0xFF) << ASHIFT))
{
}

Color::Color(float r, float g, float b, float a) :
	r(r * 255), g(g * 255), b( b * 255), a(a * 255)
{
	rgb = ((this->r & 0xFF) << RSHIFT) |
		  ((this->g & 0xFF) << GSHIFT) |
		  ((this->b & 0xFF) << BSHIFT) |
		  ((this->a & 0xFF) << ASHIFT);
}

Color::Color(RT::Vec4f &color)
{
	Set(color);
}

int Color::GetRed() const
{
	return r;
}

int Color::GetGreen() const
{
	return g;
}

int Color::GetBlue() const
{
	return b;
}

int Color::GetAlpha() const
{
	return a;
}

int Color::GetRGB() const
{
	return rgb;
}

void Color::Set(int r, int g, int b, int a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Color::Set(RT::Vec4f &color)
{
	Set(color.x, color.y, color.z, color.w);
}

void Color::SetRed(int r)
{
	this->r = r;
}

void Color::SetGreen(int g)
{
	this->g = g;
}

void Color::SetBlue(int b)
{
	this->b = b;
}

void Color::GetAlpha(int a)
{
	this->a = a;
}

void Color::SetRGB(int rgb)
{
	this->rgb = rgb;
}
