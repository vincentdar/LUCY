#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

namespace LUCY
{
	class Logger
	{
	private:

	public:
		static void PrintLn(std::string str);
		static void Clear();
	};
}


