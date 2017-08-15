#ifndef __MULTI_JITTERED_H__
#define __MULTI_JITTERED_H__

#include "..\abstract\Sampler.h"

class MultiJittered : public Sampler
{
private:
	virtual void GenerateSamples();
	void ShuffelXCoordinates();
	void ShuffelYCoordinates();

public:
	MultiJittered();
	MultiJittered(const int numSamples, 
				  const int numSets = 83);
	MultiJittered(const MultiJittered &other);

	virtual Sampler *Clone() const;
};

#endif //__MULTI_JITTERED_H__
