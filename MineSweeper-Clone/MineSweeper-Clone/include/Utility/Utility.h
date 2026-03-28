#pragma once

#include <iostream>
#include <limits>

namespace N_Utility
{
	// Provides helper functions for console operations and input handling
	class Utility
	{
		public:
			static void clearConsole();         // Clears the console screen (platform-dependent)
			static void waitForEnter();         // Waits for user to press Enter
			static void clearInputBuffer();     // Clears remaining input buffer
	};
}