#include "Utility/Utility.h"


namespace N_Utility
{
	void Utility::clearConsole()
	{
#ifdef _WIN32
		system("cls");             // Windows
#else
		(void)system("clear");     // Unix/Linux
#endif
	}

	void Utility::waitForEnter()
	{
		// Clear buffer then wait for Enter key
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}

	void Utility::clearInputBuffer()
	{
		// Discards leftover input to avoid invalid reads
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}