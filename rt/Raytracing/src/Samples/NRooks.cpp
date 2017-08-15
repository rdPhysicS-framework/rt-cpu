#include "NRooks.h"
#include "..\Util\Util.h"
#include "..\raytracer\Canvas.h"

NRooks::NRooks() :
	Sampler(1, 83)
{
	GenerateSamples();
}

NRooks::NRooks(const int numSamples,
		       const int numSets) :
	Sampler(numSamples, numSets)
{
	GenerateSamples();
}

NRooks::NRooks(const NRooks &other) :
	Sampler(other)
{
	GenerateSamples();
}

Sampler * NRooks::Clone() const
{
	return new NRooks(*this);
}

void NRooks::GenerateSamples()
{
	int n = static_cast<int>(sqrt(static_cast<float>(numSamples)));

	for (int i = 0; i < numSets; i++)
	{
		for (int j = 0; j < numSamples; j++)
		{
			RT::Vec2f pv;
			pv.x = ((j + randFloat()) / numSamples);
			pv.y = ((j + randFloat()) / numSamples);

			samples.push_back(pv);
		}
	}

	ShuffelXCoordinates();
	ShuffelYCoordinates();
}

void NRooks::ShuffelXCoordinates()
{
	for (int i = 0; i < numSets; i++)
	{
		for (int j = 0; j < numSamples; j++)
		{
			int target = randInt() % numSamples + i * numSamples;
			float temp = samples[j + i * numSamples + 1].x;
			samples[j + i * numSamples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
	}
}

void NRooks::ShuffelYCoordinates()
{
	for (int i = 0; i < numSets; i++)
	{
		for (int j = 0; j < numSamples; j++)
		{
			int target = randInt() % numSamples + i * numSamples;
			float temp = samples[j + i * numSamples + 1].y;
			samples[j + i * numSamples + 1].y = samples[target].y;
			samples[target].y = temp;
		}
	}
}
