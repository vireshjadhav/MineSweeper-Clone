#include "Game/Timer.h"

namespace N_Game
{
	// Constructor: initializes max time and sets timer as not running
	Timer::Timer(int maxTimeSeconds) : maxTime(maxTimeSeconds), isRunning(false) {}

	// Starts the timer by recording current time
	void Timer::start()
	{
		startTime = std::chrono::steady_clock::now();		// Capture start time
		isRunning = true;									// Mark timer as active
	}

	// Returns remaining time in seconds
	int Timer::getRemainingSeconds() const
	{
		// If timer hasn't started yet, return full time
		if (!isRunning) return maxTime;

		// Get current time
		auto now = std::chrono::steady_clock::now();

		// Calculate elapsed time in seconds
		int elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

		// Remaining time = total time - elapsed time
		int remaining = maxTime - elapsed;

		// Ensure value never goes below 0
		return (remaining > 0) ? remaining : 0;
	}

	// Resets timer (does NOT restart automatically)
	void Timer::reset()
	{
		isRunning = false;			// Timer stopped, but startTime not updated
	}

	// Checks if time has expired
	bool Timer::isTimeUp() const
	{
		// Time is up when remaining time reaches zero
		return getRemainingSeconds() == 0;
	}
}