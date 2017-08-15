#include "Regular.h"
#include "..\raytracer\Canvas.h"

Regular::Regular() :
	Sampler(1, 83)
{
	GenerateSamples();
}

Regular::Regular(const int numSamples,
				 const int numSets) :
	Sampler(numSamples, numSets)
{
	GenerateSamples();
}

Regular::Regular(const Regular &other) :
	Sampler(other)
{
	GenerateSamples();
}

void Regular::GenerateSamples()
{
	int n = static_cast<int>(sqrt(numSamples));

	for (int i = 0; i < numSets; i++)
		for (int y = 0; y < n; y++)
			for (int x = 0; x < n; x++)
				samples.push_back(RT::Vec2f(
									((x + 0.5f) / n),
									((y + 0.5f) / n)));
}


Sampler *Regular::Clone() const
{
	return new Regular(*this);
}
