#include "Logger.h"

namespace LUCY
{
	void Logger::PrintLn(std::string str)
	{
		/*outstream.open(LOG_FILE_PATH);

		outstream << str << std::endl;*/

		std::cout << str << std::endl;
	}
	void Logger::Clear()
	{
		system("CLS");
	}
}