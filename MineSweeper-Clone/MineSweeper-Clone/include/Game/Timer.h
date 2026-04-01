#pragma once

#include <chrono>

namespace N_Game
{
	class Timer
	{
	private:
		// Stores the starting time point using steady_clock (safe for time intervals)
		std::chrono::time_point<std::chrono::steady_clock> startTime;

		// Maximum allowed time in seconds for the game
		int maxTime;

		// Indicates whether the timer is currently running
		bool isRunning;

	public:
		// Constructor: initializes timer with given max time (in seconds)
		Timer(int maxTimeSeconds);

		// Starts the timer (records current time as start point)
		void start();

		// Returns remaining time in seconds (maxTime - elapsed time)
		int getRemainingSeconds() const;

		// Resets the timer (does not automatically start it)
		void reset();

		// Returns true if elapsed time has reached or exceeded maxTime
		bool isTimeUp() const;
	};
}