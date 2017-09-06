#pragma once

#include <SDL2/SDL.h>

namespace Util {

class Clock
{
public:
	Clock();

	double GetTotalElapsedSeconds() const;
private:
	using Counter = decltype(SDL_GetPerformanceCounter());

	Counter mStartTime;
	double mInverseFrequency;
};

}
