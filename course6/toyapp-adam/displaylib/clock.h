#pragma once

#include <SDL2/SDL.h>

namespace Display {

class Clock
{
public:
	Clock();

	double GetTotalElapsedSeconds() const;
private:
	using Counter = decltype(SDL_GetPerformanceCounter());

	Counter mFirst;
	double mInverseFrequency;
};

}
