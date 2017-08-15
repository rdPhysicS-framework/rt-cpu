#ifndef	 __SAMPLER_H__
#define	 __SAMPLER_H__

#include <vector>
#include <RTmath.h>


class Sampler
{
protected:
	int numSamples;
	int numSets;
	unsigned long count;
	int jump;

	std::vector<RT::Vec2f> samples;
	std::vector<RT::Vec2f> diskSamples;
	std::vector<RT::Vec3f> hemisphereSamples;
	std::vector<int> shuffledIndices;

public:
	Sampler(const int numSamples, 
			const int numSets);
	Sampler(const Sampler &other);
	virtual ~Sampler() {}

	inline int GetNumSamples() const { return numSamples; }
	inline int GetNumSets() const { return numSets; }

	virtual void GenerateSamples() = 0;
	virtual Sampler *Clone() const = 0;

	void SetupShuffledIndices();
	void MapSamplesToUnitDisk();
	void MapSamplesToHemisphere(const float e);

	RT::Vec2f SampleUnitSquare();
	RT::Vec2f SampleUnitDisk();
	RT::Vec3f SampleHemisphere();

};

#endif //__SAMPLER_H__
