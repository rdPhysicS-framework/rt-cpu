#ifndef	 __MESH_SPHERE_H__
#define	 __MESH_SPHERE_H__

#include "..\compound\Compound.h"

class Mesh;

class MeshSphere : public Compound
{
private:
	RT::Vec3f center;
	RT::Vec3f size;
	Mesh *mesh;
	//AbsMaterial *material;
	float radius;

	void ComputeBoundingBox();

public:
	MeshSphere(const RT::Vec3f &center, 
			   AbsMaterial *material, 
			   float radius, 
			   const int slices, 
			   const int stacks);

	void CreateFlatSphere(const int slices, const int stacks);
	void CreateSmoothSphere(const int slices, const int stacks);
	virtual bool Intersect(Ray &ray, float &distance,
						   Result &result);
};

#endif //__MESH_SPHERE_H__
