#include "Random.h"
#include "..\raytracer\Canvas.h"
#include "..\Util\Util.h"
#include <time.h>

Random::Random() :
	Sampler(1, 83)
{
	GenerateSamples();
}

Random::Random(const int numSamples,
			   const int numSets) :
	Sampler(numSamples, numSets)
{
	GenerateSamples();
}

Random::Random(const Random &other) :
	Sampler(other)
{
	GenerateSamples();
}

Sampler *Random::Clone() const
{
	return new Random(*this);
}

void Random::GenerateSamples()
{
	//setRandSeed(time(NULL));

	for(int i = 0; i < numSets; i++)
		for (int j = 0; j < numSamples; j++)
		{
			samples.push_back(
				RT::Vec2f(randFloat(), 
						  randFloat())
			);
		}
}
