#include "Box.h"
#include "..\primitivas\Result.h"
#include "..\raytracer\Ray.h"
#include "..\Util\Util.h"
#include "..\Util\BBox.h"

Box::Box(RT::Vec3f &position, 
		 RT::Vec3f &size,
		 AbsMaterial *material) :
	Primitive(material),
	position(position),
	size(size)
{}

RT::Vec3f Box::GetNormalAt(RT::Vec3f &pos)
{
	float distance[6];
	distance[0] = fabs(size.x - position.x);
	distance[1] = fabs(size.x + size.x - position.x);
	distance[2] = fabs(size.y - position.y);
	distance[3] = fabs(size.y + size.y - position.y);
	distance[4] = fabs(size.z - position.z);
	distance[5] = fabs(size.z + size.z - position.z);

	int b = 0;
	float dist = distance[0];
	for (int i = 1; i < 6; i++)
	{
		if (distance[i] < dist)
		{
			dist = distance[i];
			b = i;
		}
	}

	return (b == 0) ? RT::Vec3f(-1, 0, 0) :
		   (b == 1) ? RT::Vec3f(1, 0, 0) :
		   (b == 2) ? RT::Vec3f(0, -1, 0) :
		   (b == 3) ? RT::Vec3f(0, 1, 0) :
		   (b == 4) ? RT::Vec3f(0, 0, -1) :
		   RT::Vec3f(0, 0, 1);
}

bool Box::Intersect(Ray &ray, float &distance, Result &result)
{
	//if (!GetBoundingBox().Intersect(ray))
		//return false;

	float dist[6];
	RT::Vec3f ip[6];

	RT::Vec3f d = ray.GetDirection();
	RT::Vec3f o = ray.GetOrigin();

	bool hit = false;


	for (int i = 0; i < 6; i++)
	{
		dist[i] = -1;
	}

	RT::Vec3f s = position + size;

	if (d.x)
	{
	    float rc = 1.0f / d.x;
		dist[0] = (position.x - o.x) * rc;
		dist[3] = (s.x - o.x) * rc;
	}

	if (d.y)
	{
		float rc = 1.0f / d.y;
		dist[1] = (position.y - o.y) * rc;
		dist[4] = (s.y - o.y) * rc;
	}

	if (d.z)
	{
		float rc = 1.0f / d.z;
		dist[2] = (position.z - o.z) * rc;
		dist[5] = (s.z - o.z) * rc;
	}

	for (int i = 0; i < 6; i++)
	{
		if (dist[i] > 0)
		{
			ip[i] = o + dist[i] * d;
			if ((ip[i].x > (position.x - EPSILON)) && (ip[i].x < (s.x + EPSILON)) &&
				(ip[i].y > (position.y - EPSILON)) && (ip[i].y < (s.y + EPSILON)) &&
				(ip[i].z > (position.z - EPSILON)) && (ip[i].z < (s.z + EPSILON)))
			{
				if (dist[i] < distance)
				{
					distance = dist[i];
					hit = true;
					RT::Vec3f pi = ray.IntersectionPoint(distance);
					result.lHitPoint = pi;
					result.wHitPoint = pi;
					result.normal = GetNormalAt(pi);
					//result.hit = hit;
				}
			}
		}
	}


	return hit;

	//if (IntersectionShadow(ray, distance))
	//{
	//	result.hit = true;
	//	return true;
	//}

	//return false;
}

BBox Box::GetBoundingBox() const
{
	RT::Vec3f aux = position + size;
	float r = (aux.x > aux.y) ? aux.x : aux.y;
	r = (aux.z > r) ? aux.z : r;

	float x0 = position.x;
	float y0 = position.y;
	float z0 = position.z;
	float x1 = position.x + r;
	float y1 = position.y + r;
	float z1 = position.z + r;

	return BBox(x0, y0, z0,
				x1, y1, z1);
}

//bool Box::IntersectionShadow(Ray &ray, float &distance)
//{
//	float dist[6];
//	RT::Vec3f ip[6];
//
//	RT::Vec3f d = ray.GetDirection();
//	RT::Vec3f o = ray.GetOrigin();
//
//	bool hit = false;
//
//
//	for (int i = 0; i < 6; i++)
//	{
//		dist[i] = -1;
//	}
//
//	RT::Vec3f s = position + size;
//
//	if (d.x)
//	{
//		float rc = 1.0f / d.x;
//		dist[0] = (position.x - o.x) * rc;
//		dist[3] = (s.x - o.x) * rc;
//	}
//
//	if (d.y)
//	{
//		float rc = 1.0f / d.y;
//		dist[1] = (position.y - o.y) * rc;
//		dist[4] = (s.y - o.y) * rc;
//	}
//
//	if (d.z)
//	{
//		float rc = 1.0f / d.z;
//		dist[2] = (position.z - o.z) * rc;
//		dist[5] = (s.z - o.z) * rc;
//	}
//
//	for (int i = 0; i < 6; i++)
//	{
//		if (dist[i] > 0)
//		{
//			ip[i] = o + dist[i] * d;
//			if ((ip[i].x > (position.x - EPSILON)) && (ip[i].x < (s.x + EPSILON)) &&
//				(ip[i].y >(position.y - EPSILON)) && (ip[i].y < (s.y + EPSILON)) &&
//				(ip[i].z >(position.z - EPSILON)) && (ip[i].z < (s.z + EPSILON)))
//			{
//				if (dist[i] < distance)
//				{
//					distance = dist[i];
//					hit = true;
//				}
//			}
//		}
//	}
//
//
//	return hit;
//}
