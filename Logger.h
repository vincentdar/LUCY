#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include <fstream>

#include "Macro.h"

namespace LUCY
{
	class Logger
	{
	private:
		/*static std::ofstream outstream;*/

	public:
		static void PrintLn(std::string str);
		static void Clear();
	};
}


