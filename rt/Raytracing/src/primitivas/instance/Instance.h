#ifndef	 __INSTANCE_H__
#define	 __INSTANCE_H__

#include "..\..\abstract\Primitive.h"
#include "..\..\Util\BBox.h"
#include <RTmath.h>

class Instance : public Primitive
{
private:
	Primitive *object;
	RT::Mat4f invMatrix;
	//RT::Vec3f normal;
	bool transformTexture;

	BBox bbox;
	static RT::Mat4f forwardMatrix;

public:
	Instance();
	Instance(Primitive *object);
	Instance(const Instance &other);
	~Instance();

	void SetObject(Primitive *obj);
	void ComputeBoundingBox();

	virtual RT::Vec3f GetNormalAt(RT::Vec3f &pos);
	virtual bool Intersect(Ray &ray, float &distance, Result &result);
	virtual BBox GetBoundingBox() const;

	Instance &Translate(const float x, const float y, const float z);
	Instance &Translate(const RT::Vec3f &pos);
	Instance &RotateX(const float angle);
	Instance &RotateY(const float angle);
	Instance &RotateZ(const float angle);
	Instance &Scale(const float x, const float y, const float z);
	Instance &Scale(const RT::Vec3f &scale);
	Instance &Scale(const float scale);
};

#endif //__INSTANCE_H__