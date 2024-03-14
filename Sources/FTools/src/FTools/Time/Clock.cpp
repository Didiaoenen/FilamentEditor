/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FTools/Time/Clock.h"

float FTools::Time::Clock::GetFramerate()
{
	return 1.0f / (__DELTA_TIME);
}

float FTools::Time::Clock::GetDeltaTime()
{
	return __DELTA_TIME * __TIME_SCALE;
}

float FTools::Time::Clock::GetDeltaTimeUnscaled()
{
	return __DELTA_TIME;
}

float FTools::Time::Clock::GetTimeSinceStart()
{
	return __TIME_SINCE_START;
}

float FTools::Time::Clock::GetTimeScale()
{
	return __TIME_SCALE;
}

void FTools::Time::Clock::Scale(float p_coeff)
{
	__TIME_SCALE *= p_coeff;
}

void FTools::Time::Clock::SetTimeScale(float p_timeScale)
{
	__TIME_SCALE = p_timeScale;
}

void FTools::Time::Clock::Initialize()
{
	__DELTA_TIME = 0.0f;

	__START_TIME = std::chrono::steady_clock::now();
	__CURRENT_TIME = __START_TIME;
	__LAST_TIME = __START_TIME;

	__INITIALIZED = true;
}

void FTools::Time::Clock::Update()
{
	__LAST_TIME = __CURRENT_TIME;
	__CURRENT_TIME = std::chrono::steady_clock::now();
	__ELAPSED = __CURRENT_TIME - __LAST_TIME;

	if (__INITIALIZED)
	{
		__DELTA_TIME = __ELAPSED.count() > 0.1 ? 0.1f : static_cast<float>(__ELAPSED.count());
		__TIME_SINCE_START += __DELTA_TIME * __TIME_SCALE;
	}
	else
		Initialize();
}