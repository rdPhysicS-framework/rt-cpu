#ifndef	 __FLAT_MESH_TRIANGLE_H__
#define	 __FLAT_MESH_TRIANGLE_H__

#include "..\..\abstract\MeshTriangle.h"

class FlatMeshTriangle : public MeshTriangle
{
public:
	FlatMeshTriangle();
	FlatMeshTriangle(Mesh *mesh, const int index0,
					 const int index1, const int index2);
	FlatMeshTriangle(const FlatMeshTriangle &other);

	virtual bool Intersect(Ray &ray, float &distance, Result &result);
};

#endif //__FLAT_MESH_TRIANGLE_H__
