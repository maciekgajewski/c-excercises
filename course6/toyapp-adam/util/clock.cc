#include "clock.h"

namespace Util {

Clock::Clock()
{
	mStartTime = SDL_GetPerformanceCounter();
	mInverseFrequency = 1.0 / static_cast<double>(SDL_GetPerformanceFrequency());
}

double Clock::GetTotalElapsedSeconds() const
{
	return (SDL_GetPerformanceCounter() - mStartTime) * mInverseFrequency;
}

}
