#ifndef	 __ABS_BTDF_H__
#define	 __ABS_BTDF_H__

#include "..\interface\BTDF.h"

class AbsBTDF : public BTDF
{
public:
	virtual ~AbsBTDF(){}
	virtual BTDF *Clone() = 0;
	virtual RT::Vec3f F(Result &result, RT::Vec3f &wt, RT::Vec3f &wo) const;
	virtual RT::Vec3f SampleF(Result &result, RT::Vec3f &wt, RT::Vec3f &wo) const = 0;
	virtual bool Tir(Result &result) const = 0;
	virtual RT::Vec3f RHO(const Result &result,
						  const RT::Vec3f &wo) const;
};


#endif //__ABS_BTDF_H__