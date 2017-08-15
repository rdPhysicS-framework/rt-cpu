#include "Sphere.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"
#include "..\Util\BBox.h"

Sphere::Sphere(RT::Vec3f &pos, 
			   float r, 
			   AbsMaterial *material) :
	Primitive(material), 
	center(pos), 
	radius(r),
	sqrRadius(r * r),
	invRadius(1.0f/r)
{
	
}

RT::Vec3f Sphere::GetNormalAt(RT::Vec3f &pos)
{
	return (pos - center).Normalize();// *invRadius;
}

bool Sphere::Intersect(Ray &ray, float &distance, Result &result)
{
	//RT::Vec3f v = ray.GetOrigin() - center;

	//float b = -v.Dot(ray.GetDirection());
	//float det = (b * b) - v.Dot(v) + sqrRadius;
	//int hit = false;

	//if (det > 0)
	//{
	//	det = sqrtf(det);

	//	float i1 = b - det;
	//	float i2 = b + det;

	//	if (i2 > 0)
	//	{
	//		if (i1 < 0)
	//		{
	//			if (i2 < distance)
	//			{
	//				hit = EOF;
	//				distance = i2;
	//				RT::Vec3f pi = ray.IntersectionPoint(distance);
	//				result.lHitPoint = pi;
	//				result.wHitPoint = pi;
	//				result.normal = GetNormalAt(pi);
	//				/*result.hit = hit;
	//				result.wHitPoint = ray.IntersectionPoint(distance);
	//				result.lHitPoint = result.wHitPoint;
	//				result.normal = GetNormalAt(result.wHitPoint);*/
	//			}
	//		}
	//		else
	//		{
	//			if (i1 < distance)
	//			{
	//				hit = true;
	//				distance = i1;
	//				RT::Vec3f pi = ray.IntersectionPoint(distance);
	//				result.lHitPoint = pi;
	//				result.wHitPoint = pi;
	//				result.normal = GetNormalAt(pi);
	//				//result.hit = hit;
	//			}
	//		}
	//	}
	//}

	//return (hit == true || hit == EOF);

	double t;
	RT::Vec3f temp = ray.GetOrigin() - center;
	double a = ray.GetDirection().SizeSQR();
	double b = 2.0 * temp.Dot(ray.GetDirection());
	double c = temp.SizeSQR() - radius * radius;
	double delta = b * b - 4.0 * a * c;

	if (delta < 0.0)
		return false;

	double e = sqrt(delta);
	double denom = 2.0 * a;

	t = (-b - e) / denom;

	if (t > 0.001)
	{
		distance = t;
		result.normal = (temp + t * ray.GetDirection()) / radius;
		result.wHitPoint = ray.IntersectionPoint(t);
		result.lHitPoint = result.wHitPoint;
		return true;
	}

	t = (-b + e) / denom;

	if (t > 0.001)
	{
		distance = t;
		result.normal = (temp + t * ray.GetDirection()) / radius;
		result.wHitPoint = ray.IntersectionPoint(t);
		result.lHitPoint = result.wHitPoint;
		return true;
	}

	return false;
}

BBox Sphere::GetBoundingBox() const
{
	float x0 = center.x - (sqrRadius + 4);
	float y0 = center.y - (sqrRadius + 4);
	float z0 = center.z - (sqrRadius + 4);
	float x1 = center.x + (sqrRadius + 4);
	float y1 = center.y + (sqrRadius + 4);
	float z1 = center.z + (sqrRadius + 4);
	return BBox(x0, y0, z0, x1, y1, z1);
}

//bool Sphere::IntersectionShadow(Ray &ray, float &distance)
//{
//	return false;
//}
