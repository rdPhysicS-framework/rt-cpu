#include "Sampler.h"
#include <algorithm>
#include "..\Util\Util.h"

Sampler::Sampler(const int numSamples,
				 const int numSets) :
	numSamples(numSamples),
	numSets(numSets),
	jump(0), count(0)
{
	samples.reserve(numSamples * numSets);
	SetupShuffledIndices();
}

Sampler::Sampler(const Sampler &other) :
	numSamples(other.numSamples),
	numSets(other.numSets),
	samples(other.samples),
	shuffledIndices(other.shuffledIndices),
	count(other.count),
	jump(other.jump)
{}

void Sampler::SetupShuffledIndices()
{
	shuffledIndices.reserve(numSamples * numSets);

	std::vector<int> indices;

	for (int i = 0; i < numSamples; i++)
		indices.push_back(i);

	for (int i = 0; i < numSets; i++)
	{
		std::random_shuffle(indices.begin(), indices.end());
		
		for (int j = 0; j < numSamples; j++)
			shuffledIndices.push_back(indices[j]);
	}
}

void Sampler::MapSamplesToUnitDisk()
{
	float r, phi;

	for (RT::Vec2f &s : samples)
	{
		RT::Vec2f sp(2.0f * s.x - 1.0f,
					 2.0f * s.y - 1.0f);

		if (sp.x > -sp.y)
		{
			if (sp.x > sp.y)
			{
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else
			{
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else
		{
			if (sp.x < sp.y)
			{
				r = -sp.y;

				if (sp.y != 0.0f)
					phi = 6 - sp.x / sp.y;
				else
					phi = 0.0f;
			}
		}

		phi *= RT_PI / 4.0;

		diskSamples.push_back(RT::Vec2f(r * cos(phi),
										r * sin(phi)));
	}
}

void Sampler::MapSamplesToHemisphere(const float e)
{
	for (RT::Vec2f &s : samples)
	{
		float cosPhi = cos(2.0 * RT_PI * s.x);
		float sinPhi = sin(2.0 * RT_PI * s.x);

		float cosTheta = pow((1.0 - s.y), 1.0 / (e + 1.0));
		float sinTheta = sqrt(1.0 - pow(cosTheta, 2));

		hemisphereSamples.push_back(RT::Vec3f(sinTheta * cosPhi, 
											  sinTheta * sinPhi, 
											  cosTheta));
	}
}

RT::Vec2f Sampler::SampleUnitSquare()
{
	if (count % numSamples == 0)
		jump = (randInt() % numSets) * numSamples;

	return samples[jump + shuffledIndices[jump + count++ % numSamples]];
}

RT::Vec2f Sampler::SampleUnitDisk()
{
	if (count % numSamples == 0)
		jump = (randInt() % numSets) * numSamples;

	return diskSamples[jump + shuffledIndices[jump + count++ % numSamples]];
}

RT::Vec3f Sampler::SampleHemisphere()
{
	if (count % numSamples == 0)
		jump = (randInt() % numSets) * numSamples;

	return hemisphereSamples[jump + shuffledIndices[jump + count++ % numSamples]];
}
