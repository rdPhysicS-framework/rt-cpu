#ifndef	 __FRESNEL_TRANSMITTER_H__
#define	 __FRESNEL_TRANSMITTER_H__

#include "..\abstract\AbsBTDF.h"

class FresnelTransmitter : public AbsBTDF
{
private:
	float etaOut;
	float etaIn;

public:
	float Fresnel(const Result &result) const;
	virtual BTDF *Clone();
	virtual RT::Vec3f SampleF(Result &result, RT::Vec3f &wt, RT::Vec3f &wo) const;
	virtual bool Tir(Result &result) const;
	
};

#endif //__FRESNEL_TRANSMITTER_H__