#ifndef	 __RANDOM_H__
#define	 __RANDOM_H__

#include "..\abstract\Sampler.h"


class Random : public Sampler
{
private:
	virtual void GenerateSamples();

public:
	Random();
	Random(const int numSamples, 
		   const int numSets = 83);
	Random(const Random &other);

	virtual Sampler *Clone() const;
};

#endif //__RANDOM_H__