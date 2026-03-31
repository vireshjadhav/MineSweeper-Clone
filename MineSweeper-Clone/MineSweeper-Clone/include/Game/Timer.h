#pragma once

#include <chrono>

namespace N_Game
{
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		int maxTime;
		bool isRunning;

	public:
		Timer(int maxTimeSeconds);

		void start();
		int getRemainingSeconds() const;
		void reset();
		bool isTimeUp() const;
	};
}