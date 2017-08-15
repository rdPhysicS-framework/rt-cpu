#include "Jittered.h"
#include "..\Util\Util.h"
#include "..\raytracer\Canvas.h"
#include <time.h>

Jittered::Jittered() :
	Sampler(1, 83)
{
	GenerateSamples();
}

Jittered::Jittered(const int numSamples, 
				   const int numSets) :
	Sampler(numSamples, numSets)
{
	GenerateSamples();
}

Jittered::Jittered(const Jittered &other) : 
	Sampler(other)
{
	GenerateSamples();
}

Sampler *Jittered::Clone() const
{
	return new Jittered(*this);
}

void Jittered::GenerateSamples()
{
	int n = static_cast<int>(sqrt(static_cast<float>(numSamples)));

	setRandSeed(time(NULL));
	for (int p = 0; p < numSets; p++)
		for (float y = 0; y < n; y++)
			for (int x = 0; x < n; x++)
			{
				RT::Vec2f sp(((x + randFloat())/n),
							 ((y + randFloat())/n));

				samples.push_back(sp);
			}

	//for (int p = 0; p < numSets; p++)
	//	for (float y = sizePixel.y; y < canvas->GetSizePixels().y; y += sizePixel.y)
	//		for (float x = sizePixel.x; x < canvas->GetSizePixels().x; x += sizePixel.x)
	//		{
	//			/*RT::Vec2f sp((x * randFloat()) / n,
	//			(y * randFloat()) / n);*/

	//			/*RT::Vec2f sp((sizePixel.x * x + randFloat())/n,
	//			(sizePixel.y * y + randFloat())/n);*/

	//			RT::Vec2f sp((x + randFloat()),
	//				(y + randFloat()));

	//			samples.push_back(sp);
	//		}
}

