#include "MultiJittered.h"
#include "..\raytracer\Canvas.h"
#include "..\Util\Util.h"
#include <time.h>

MultiJittered::MultiJittered() :
	Sampler(1, 83)
{
	GenerateSamples();
}

MultiJittered::MultiJittered(const int numSamples, 
							 const int numSets) :
	Sampler(numSamples, numSets)
{
	GenerateSamples();
}

MultiJittered::MultiJittered(const MultiJittered &other) :
	Sampler(other)
{
	GenerateSamples();
}

Sampler *MultiJittered::Clone() const
{
	return new MultiJittered(*this);
}

void MultiJittered::GenerateSamples()
{
	//setRandSeed(time(NULL));

	int n = static_cast<int>(sqrt(numSamples));

	float sw = 1.0f / static_cast<float>(numSamples);

	float s = numSamples * numSets;
	for (int i = 0; i < s; i++)
	{
		samples.push_back(RT::Vec2f());
	}

	for (int k = 0; k < numSets; k++)
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				samples[i * n + j + k * numSamples].x = ((i * n + j) * sw + randFloat(0.0f, sw));
				samples[i * n + j + k * numSamples].y = ((j * n + i) * sw + randFloat(0.0f, sw));
			}
		}

	ShuffelXCoordinates();
	ShuffelYCoordinates();
}

void MultiJittered::ShuffelXCoordinates()
{
	int n = static_cast<int>(sqrt(numSamples));

	for (int p = 0; p < numSets; p++)
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int k = randInt(j, n - 1);
				float t = samples[i * n + j + p * numSamples].x;
				samples[i * n + j + p * numSamples].x = samples[i * n + k + p * numSamples].x;
				samples[i * n + k + p * numSamples].x = t;
			}
		}
}

void MultiJittered::ShuffelYCoordinates()
{
	int n = static_cast<int>(sqrt(numSamples));

	for (int p = 0; p < numSets; p++)
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int k = randInt(j, n - 1);
				float t = samples[i * n + j + p * numSamples].y;
				samples[i * n + j + p * numSamples].y = samples[i * n + k + p * numSamples].y;
				samples[i * n + k + p * numSamples].y = t;
			}
		}
}
