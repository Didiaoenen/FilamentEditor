/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FTools/Utils/Random.h"

std::default_random_engine FTools::Utils::Random::__GENERATOR;

int FTools::Utils::Random::Generate(int p_min, int p_max)
{
	std::uniform_int_distribution<int> distribution(p_min, p_max);
	return distribution(__GENERATOR);
}

float FTools::Utils::Random::Generate(float p_min, float p_max)
{
	std::uniform_real_distribution<float> distribution(p_min, p_max);
	return distribution(__GENERATOR);
}

bool FTools::Utils::Random::CheckPercentage(float p_percentage)
{
	std::uniform_real_distribution<float> distribution(0.0f, 100.0f);
	return distribution(__GENERATOR) <= p_percentage;
}
