#pragma once

#include <chrono>

namespace Util {

class Clock
{
	using HiResClock = std::chrono::high_resolution_clock;
public:
	Clock()
	:	mStartTime(HiResClock::now())
	{}

	double GetTotalElapsedSeconds() const
	{
		return std::chrono::duration<double>(HiResClock::now() - mStartTime).count();
	}
private:
	std::chrono::time_point<HiResClock> mStartTime;
};

}