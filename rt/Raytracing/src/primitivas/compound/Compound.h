#ifndef	 __COMPOUND_H__
#define	 __COMPOUND_H__

#include "..\..\abstract\Primitive.h"
#include "..\..\Util\BBox.h"
#include <vector>

class Compound : public Primitive
{
private:
	void DeleteObjects();

protected:
	std::vector<Primitive*> objects;
	BBox bbox;
	RT::Vec3f normal;

public:
	Compound();
	Compound(AbsMaterial *material);
	Compound(const Compound &other);
	~Compound();

	Compound *clone() const;

	inline int GetSize() const { return objects.size(); }
	virtual void SetMaterial(AbsMaterial *_material);

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, 
						   Result &result);
	//virtual bool IntersectionShadow(Ray &ray, float &distance);
	virtual BBox GetBoundingBox() const;
	virtual void AddObject(Primitive *object);
};
#endif //__COMPOUND_H__