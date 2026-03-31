#include "Game/Timer.h"

namespace N_Game
{
	Timer::Timer(int maxTimeSeconds) : maxTime(maxTimeSeconds), isRunning(false) {}

	void Timer::start()
	{
		startTime = std::chrono::steady_clock::now();
		isRunning = true;
	}

	int Timer::getRemainingSeconds() const
	{
		if (!isRunning) return maxTime;

		auto now = std::chrono::steady_clock::now();
		int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
		int remaining = maxTime - elapsed;

		return (remaining > 0) ? remaining : 0;
	}

	void Timer::reset()
	{
		isRunning = false;
	}

	bool Timer::isTimeUp() const
	{
		return getRemainingSeconds() == 0;
	}
}