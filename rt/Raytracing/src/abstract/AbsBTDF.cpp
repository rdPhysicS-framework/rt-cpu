#include "AbsBTDF.h"

RT::Vec3f AbsBTDF::F(Result & result, RT::Vec3f & wt, RT::Vec3f & wo) const
{
	return RT::Vec3f();
}

RT::Vec3f AbsBTDF::RHO(const Result & result, const RT::Vec3f & wo) const
{
	return RT::Vec3f();
}
