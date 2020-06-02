#include "Logger.h"

namespace LUCY
{
	void Logger::PrintLn(std::string str)
	{
		std::cout << str << std::endl;
	}
	void Logger::Clear()
	{
		system("CLS");
	}
}