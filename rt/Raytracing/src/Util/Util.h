#pragma once
#include <stdlib.h>
#define INFINITE 10000000000.0
#define TRACEDEPTH 6

#define EPSILON 0.0001

#define FILE_NAME "raytrace.png"

#define RMASK 0x000000FF
#define GMASK 0x0000FF00
#define BMASK 0x00FF0000
#define AMASK 0xFF000000

#define RSHIFT 0
#define GSHIFT 8
#define BSHIFT 16
#define ASHIFT 24

#include <RTmath.h>

#define BLACK RT::Vec3f(0, 0, 0)
#define WHITE RT::Vec3f(1, 1, 1)
#define RED   RT::Vec3f(1, 0, 0)
#define GREEN RT::Vec3f(0, 1, 0)
#define BLUE  RT::Vec3f(0, 0, 1)

#define VERY_LOW  4
#define LOW       16
#define MEDIUM    64
#define HIGH      100
#define VERY_HIGH 144
#define ULTRA     256

#define INVPI 1.0 / RT_PI

inline int randInt() 
{ 
	return rand();
}

inline void setRandSeed(const int seed) 
{ 
	srand(seed); 
}

inline float randFloat() 
{ 
	return (float)randInt() / RAND_MAX; 
}

inline float randFloat(int l, float h) 
{ 
	return randFloat() * (h - l) + l; 
}

inline int randInt(int l, int h) 
{ 
	return (int)(randFloat(0, h - l + 1) + l); 
}

inline float clamp(double x, double min, double max) 
{ 
	return (x < min) ? min : (x > max) ? max : x; 
}

inline double min(double v1, double v2)
{
	return (v1 < v2) ? v1 : v2;
}

inline double max(double v1, double v2)
{
	return (v1 > v2) ? v1 : v2;
}

inline RT::Vec3f transformPoint(RT::Mat4f &m, const RT::Vec3f &p)
{
	return RT::Vec3f(m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3],
					 m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3],
					 m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3]);
}

inline RT::Vec3f transformDirection(RT::Mat4f &m, const RT::Vec3f &d)
{
	return RT::Vec3f(m[0][0] * d.x + m[0][1] * d.y + m[0][2] * d.z,
					 m[1][0] * d.x + m[1][1] * d.y + m[1][2] * d.z,
					 m[2][0] * d.x + m[2][1] * d.y + m[2][2] * d.z);
}

inline RT::Vec3f transformNormal(RT::Mat4f &m, const RT::Vec3f &n)
{
	return RT::Vec3f(m[0][0] * n.x + m[1][0] * n.y + m[2][0] * n.z,
					 m[0][1] * n.x + m[1][1] * n.y + m[2][1] * n.z,
					 m[0][2] * n.x + m[1][2] * n.y + m[2][2] * n.z)
			.Normalize();
}