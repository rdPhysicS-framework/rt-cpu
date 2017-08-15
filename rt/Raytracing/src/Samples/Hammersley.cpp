#include "Hammersley.h"
#include "..\raytracer\Canvas.h"

Hammersley::Hammersley() :
	Sampler(1, 83)
{
	GenerateSamples();
}

Hammersley::Hammersley(const int numSamples, 
					   const int numSets) :
	Sampler(numSamples, numSets)
{
	GenerateSamples();
}

Hammersley::Hammersley(const Hammersley &other) :
	Sampler(other)
{
	GenerateSamples();
}

Sampler *Hammersley::Clone() const
{
	return new Hammersley(*this);
}

void Hammersley::GenerateSamples()
{
	for(int i = 0; i < numSets; i++)
		for (int j = 0; j < numSamples; j++)
		{
			samples.push_back(
				RT::Vec2f((j / numSamples),
						  Phi(j))
			);
		}
}

float Hammersley::Phi(int index)
{
	double x = 0.0;
	double f = 0.5;

	while (index != 0)
	{
		x += f * static_cast<double>(index % 2);
		index /= 2;
		f *= 0.5;
	}

	return static_cast<float>(x);
}
