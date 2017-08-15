#ifndef	 __NROOKS_H__
#define	 __NROOKS_H__

#include "..\abstract\Sampler.h"

class NRooks : public Sampler
{
private:
	virtual void GenerateSamples();
	void ShuffelXCoordinates();
	void ShuffelYCoordinates();

public:
	NRooks();
	NRooks(const int numSamples, 
		   const int numSets = 83);
	NRooks(const NRooks &other);

	virtual Sampler *Clone() const;
};

#endif //__NROOKS_H__
