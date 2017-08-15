#ifndef	 __MESH_TRIANGLE_H__
#define	 __MESH_TRIANGLE_H__

#include "Primitive.h"
#include <RTmath.h>
class Mesh;

class MeshTriangle : public Primitive
{
protected:
	Mesh *mesh;
	int index0, index1, index2;
	RT::Vec3f normal;
	float area;

	float InterpolateU(const float beta, const float gama) const;
	float InterpolateV(const float beta, const float gama) const;
public:
	MeshTriangle();
	MeshTriangle(Mesh *mesh, const int index0,
				 const int index1, const int index2);
	MeshTriangle(const MeshTriangle &other);

	virtual ~MeshTriangle();

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, Result &result) = 0;

	void ComputeNormal(const bool reverseNormal);
	virtual BBox GetBoundingBox() const;
};

#endif //__MESH_TRIANGLE_H__
