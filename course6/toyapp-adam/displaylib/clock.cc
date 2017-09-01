#include "clock.h"

namespace Display {

Clock::Clock()
{
	mFirst = SDL_GetPerformanceCounter();
	mInverseFrequency = 1.0 / static_cast<double>(SDL_GetPerformanceFrequency());
}

double Clock::GetTotalElapsedSeconds() const
{
	const auto delta = SDL_GetPerformanceCounter() - mFirst;
	return delta * mInverseFrequency;
}

}
