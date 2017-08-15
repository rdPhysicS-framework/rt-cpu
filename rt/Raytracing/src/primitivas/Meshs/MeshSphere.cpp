#include "MeshSphere.h"
#include "Mesh.h"
#include "FlatMeshTriangle.h"
#include "..\Triangle.h"
#include "..\..\abstract\AbsMaterial.h"
#include <vector>

MeshSphere::MeshSphere(const RT::Vec3f &center, 
					   AbsMaterial *material,
					   float radius, 
					   const int slices, 
					   const int stacks) :
	Compound(material), center(center),
	radius(radius)//, mesh(new Mesh)
{
	CreateFlatSphere(slices, stacks);
}

void MeshSphere::CreateFlatSphere(const int slices, const int stacks)
{
	std::vector<RT::Vec3f> vertices;
	std::vector<int> indices;

	for (int slice = 0; slice <= slices; slice++)
	{
		double theta = slice * RT_PI / slices;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);

		for (int stack = 0; stack < stacks; stack++)
		{
			double phi = stack * RT_2PI / stacks;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);

			float x = center.x + radius * static_cast<float>(cosPhi * sinTheta);
			float y = center.y + radius * static_cast<float>(cosTheta);
			float z = center.z + radius * static_cast<float>(sinPhi * sinTheta);

			vertices.push_back(RT::Vec3f(x, y, z));

			if (size.x < x)
				size.x = x;
			if (size.y < y)
				size.y = y;
			if (size.z < z)
				size.z = z;
		}
	}

	for (int z = 0; z <= slices; z++)
	{
		for (int x = 0; x < stacks; x++)
		{
			int zero = x + z * stacks;
			int one = (x + 1) + z * stacks;
			int two = x + (z + 1) * stacks;
			int three = (x + 1) + (z + 1) * stacks;

			AddObject(new Triangle(vertices[one],
								   vertices[three],
								   vertices[two],
								   (AbsMaterial*)material->Clone()));

			AddObject(new Triangle(vertices[one],
								   vertices[two],
								   vertices[zero],
								   (AbsMaterial*)material->Clone()));
		}
	}

	ComputeBoundingBox();

	//int k = 1;

	//for (int j = 0; j <= slices - 1; j++) {
	//	// define vertices

	//	RT::Vec3f v0(0, 1, 0);																		// top (north pole)

	//	RT::Vec3f v1(sin(2.0 * RT_PI * j / slices) * sin(RT_PI * k / stacks), 			// bottom left
	//		cos(RT_PI * k / stacks),
	//		cos(2.0 * RT_PI * j / slices) * sin(RT_PI * k / stacks));

	//	RT::Vec3f v2(sin(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * k / stacks), 		// bottom  right
	//		cos(RT_PI * k / stacks),
	//		cos(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * k / stacks));

	//	Triangle* triangle_ptr = new Triangle(v0, v1, v2, (AbsMaterial*)material->Clone());
	//	objects.push_back(triangle_ptr);
	//}


	//// define the bottom triangles which all touch the south pole

	//k = stacks - 1;

	//for (int j = 0; j <= slices - 1; j++) {
	//	// define vertices

	//	RT::Vec3f v0(sin(2.0 * RT_PI * j / slices) * sin(RT_PI * k / stacks), 			// top left
	//		cos(RT_PI * k / stacks),
	//		cos(2.0 * RT_PI * j / slices) * sin(RT_PI * k / stacks));

	//	RT::Vec3f v1(0, -1, 0);																		// bottom (south pole)		

	//	RT::Vec3f v2(sin(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * k / stacks), 		// top right 
	//		cos(RT_PI * k / stacks),
	//		cos(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * k / stacks));

	//	Triangle* triangle_ptr = new Triangle(v0, v1, v2, (AbsMaterial*)material->Clone());
	//	objects.push_back(triangle_ptr);
	//}



	////  define the other triangles

	//for (int k = 1; k <= stacks - 2; k++) {
	//	for (int j = 0; j <= slices - 1; j++) {
	//		// define the first triangle

	//		// vertices

	//		RT::Vec3f v0(sin(2.0 * RT_PI * j / slices) * sin(RT_PI * (k + 1) / stacks), 				// bottom left, use k + 1, j
	//			cos(RT_PI * (k + 1) / stacks),
	//			cos(2.0 * RT_PI * j / slices) * sin(RT_PI * (k + 1) / stacks));

	//		RT::Vec3f v1(sin(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * (k + 1) / stacks), 		// bottom  right, use k + 1, j + 1
	//			cos(RT_PI * (k + 1) / stacks),
	//			cos(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * (k + 1) / stacks));

	//		RT::Vec3f v2(sin(2.0 * RT_PI * j / slices) * sin(RT_PI * k / stacks), 					// top left, 	use k, j
	//			cos(RT_PI * k / stacks),
	//			cos(2.0 * RT_PI * j / slices) * sin(RT_PI * k / stacks));

	//		Triangle* triangle_ptr1 = new Triangle(v0, v1, v2, (AbsMaterial*)material->Clone());
	//		objects.push_back(triangle_ptr1);


	//		// define the second triangle

	//		// vertices

	//		v0 = RT::Vec3f(sin(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * k / stacks), 			// top right, use k, j + 1
	//			cos(RT_PI * k / stacks),
	//			cos(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * k / stacks));

	//		v1 = RT::Vec3f(sin(2.0 * RT_PI * j / slices) * sin(RT_PI * k / stacks), 				// top left, 	use k, j
	//			cos(RT_PI * k / stacks),
	//			cos(2.0 * RT_PI * j / slices) * sin(RT_PI * k / stacks));

	//		v2 = RT::Vec3f(sin(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * (k + 1) / stacks), 	// bottom  right, use k + 1, j + 1
	//			cos(RT_PI * (k + 1) / stacks),
	//			cos(2.0 * RT_PI * (j + 1) / slices) * sin(RT_PI * (k + 1) / stacks));

	//		Triangle* triangle_ptr2 = new Triangle(v0, v1, v2, (AbsMaterial*)material->Clone());
	//		objects.push_back(triangle_ptr2);
	//	}
	//}

	//ComputeBoundingBox();
}

void MeshSphere::ComputeBoundingBox()
{
	float x0 = center.x - size.x;
	float y0 = center.y - size.y;
	float z0 = center.z - size.z;
	float x1 = center.x + size.x;
	float y1 = center.y + size.y;
	float z1 = center.z + size.z;

	bbox = BBox(x0, y0, z0, x1, y1, z1);
}

void MeshSphere::CreateSmoothSphere(const int slices, const int stacks)
{
}

bool MeshSphere::Intersect(Ray &ray, float &distance, Result &result)
{
	if (!bbox.Intersect(ray))
		return false;

	return Compound::Intersect(ray, distance, result);
}
