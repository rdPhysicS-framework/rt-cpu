#ifndef	 __JITTERED_H__
#define	 __JITTERED_H__

#include "..\abstract\Sampler.h"

class Jittered : public Sampler
{
private:
	virtual void GenerateSamples();

public:
	Jittered();
	Jittered(const int numSamples, 
			 const int numSets = 83);
	Jittered(const Jittered &other);

	virtual Sampler *Clone() const;
};

#endif //__JITTERED_H__
