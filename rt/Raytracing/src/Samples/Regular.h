#ifndef	 __REGULAR_H__
#define	 __REGULAR_H__

#include "..\abstract\Sampler.h"


class Regular : public Sampler
{
private:
	virtual void GenerateSamples();
	
public:
	Regular();
	Regular(const int numSamples, 
			const int numSets = 83);
	Regular(const Regular &other);

	virtual Sampler *Clone() const;
};

#endif //__REGULAR_H__
