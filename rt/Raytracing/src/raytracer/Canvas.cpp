#include "Canvas.h"
#include "Color.h"
#include "..\Util\Util.h"
#include "..\Samples\Regular.h"
#include "..\abstract\AbsCamera.h"

Canvas::Canvas(int w, int h)
{
	img = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	float wx1 = -(GetAspect() * 0.5f);
	float wx2 = -wx1;

	float wy1 = -(10.0f / 2.0f);
	float wy2 = -wy1;

	sizePixels.x = (wx2 - wx1) / GetWidthImg();
	sizePixels.y = (wy2 - wy1) / GetHeightImg();
}

Canvas::~Canvas()
{
	SDL_FreeSurface(img);
	img = nullptr;

	delete sampler;
	sampler = nullptr;
}

void Canvas::Saturate(RT::Vec3f &color)
{
	color.x = (color.x > 1.0f ? 1.0f : color.x < 0.0f ? 0.0f : color.x);
	color.y = (color.y > 1.0f ? 1.0f : color.y < 0.0f ? 0.0f : color.y);
	color.z = (color.z > 1.0f ? 1.0f : color.z < 0.0f ? 0.0f : color.z);
}

int Canvas::ToRGB(RT::Vec3f &color)
{
	Saturate(color);
	int r = static_cast<int>(color.x * 255);
	int g = static_cast<int>(color.y * 255);
	int b = static_cast<int>(color.z * 255);

	return Color(r, g, b).GetRGB();
}

void Canvas::SetSampler(Sampler *sampler)
{
	this->sampler = sampler;
}

void Canvas::Set(int x, int y, RT::Vec3f &color)
{
	int invR = GetWidthImg() - x - 1;
	Uint32 *pixel = (Uint32 *)img->pixels + (y * img->pitch / 4) + invR;
	*pixel = ToRGB(color);
	//std::cout << *pixel << std::endl;
}

void Canvas::Save()
{
	IMG_SavePNG(img, FILE_NAME);
}
