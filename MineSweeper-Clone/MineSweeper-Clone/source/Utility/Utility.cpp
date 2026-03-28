#include "Utility/Utility.h"


namespace N_Utility
{
	void Utility::clearConsole()
	{
#ifdef _WIN32
		system("cls");
#else
		(void)system("clear");
#endif
	}

	void Utility::waitForEnter()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
	}

	void Utility::clearInputBuffer()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}