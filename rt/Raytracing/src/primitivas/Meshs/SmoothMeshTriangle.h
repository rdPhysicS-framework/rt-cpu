#ifndef	 __SMOOTH_MESH_TRIANGLE_H__
#define	 __SMOOTH_MESH_TRIANGLE_H__

#include "..\..\abstract\MeshTriangle.h"

class SmoothMeshTriangle : public MeshTriangle
{
protected:
	RT::Vec3f InterpolateNormal(const float beta,
								const float gamma);
public:
	SmoothMeshTriangle();
	SmoothMeshTriangle(Mesh *mesh, const int index0,
					   const int index1, const int index2);
	SmoothMeshTriangle(const SmoothMeshTriangle &other);

	virtual bool Intersect(Ray &ray, float &distance, Result &result);
};

#endif //__SMOOTH_MESH_TRIANGLE_H__
