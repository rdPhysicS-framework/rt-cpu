#ifndef	 __CANVAS_H__
#define	 __CANVAS_H__

#include <SDL.h>
#include <SDL_image.h>
#include <RTmath.h>

class Sampler;
class AbsCamera;

class Canvas
{
private:
	SDL_Surface *img;

	RT::Vec2f sizePixels;
	Sampler *sampler;

	void Saturate(RT::Vec3f &color);
	int ToRGB(RT::Vec3f &color);

public:
	Canvas(int w, int h);
	~Canvas();

	inline const RT::Vec2f &GetSizePixels() const { return sizePixels; }
	inline float GetWidthImg() const { return static_cast<float>(img->w); }
	inline float GetHeightImg() const { return static_cast<float>(img->h); }
	inline float GetAspect() const { return (GetWidthImg() / GetHeightImg()) * 10.0f; }
	inline Sampler *GetSampler() const { return sampler; }

	void SetSampler(Sampler *sampler);
	void Set(int x, int y, RT::Vec3f &color);

	void Save();
};

#endif //__CANVAS_H__
