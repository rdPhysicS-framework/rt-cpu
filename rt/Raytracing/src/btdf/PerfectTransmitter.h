#ifndef	 __PERFECT_TRANSMITTER_H__
#define	 __PERFECT_TRANSMITTER_H__

#include "..\abstract\AbsBTDF.h"
#include <RTmath.h>

class PerfectTransmitter : public AbsBTDF
{
private:
	RT::Vec3f color;
	float kt;
	float ior;
	
public:
	PerfectTransmitter(RT::Vec3f &color, float kt, float ior);
	PerfectTransmitter(const PerfectTransmitter &other);

	inline void SetKt(float kt) { this->kt = kt; }
	inline void SetIor(float ior) { this->ior = ior; }
	inline float GetKt() const { return kt; }
	inline float GetIor() const { return ior; }

	virtual BTDF *Clone();
	virtual RT::Vec3f SampleF(Result &result, 
							  RT::Vec3f &wt, 
							  RT::Vec3f &wo) const;
	virtual bool Tir(Result &result) const;
};

#endif //__PERFECT_TRANSMITTER_H__