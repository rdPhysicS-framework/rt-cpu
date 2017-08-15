#ifndef	 __ABS_LIGHT_H__
#define	 __ABS_LIGHT_H__

#include "..\interface\Light.h"

class AbsLight : public Light
{
protected:
	bool shadows;

public:
	AbsLight(bool shadows = true);
	AbsLight(const AbsLight &other);
	virtual ~AbsLight() {}

	inline bool GetShadows() const { return shadows; }

	virtual AbsLight *Clone() = 0;
	virtual RT::Vec3f GetDirection(Result &result) = 0;
	virtual RT::Vec3f L(Result &result);
	virtual float G(Result &result);
	virtual float PDF(Result &result);
	virtual bool InShadow(Ray &ray, Result &result) = 0;
};

#endif //__ABS_LIGHT_H__
