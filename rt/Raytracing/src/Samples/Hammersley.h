#ifndef	 __HAMMESLEY_H__
#define	 __HAMMESLEY_H__

#include "..\abstract\Sampler.h"

class Hammersley : public Sampler
{
private:
	virtual void GenerateSamples();
	float Phi(int index);

public:
	Hammersley();
	Hammersley(const int numSamples, 
			   const int numSets = 83);
	Hammersley(const Hammersley &other);

	virtual Sampler *Clone() const;
};

#endif //__HAMMESLEY_H__
