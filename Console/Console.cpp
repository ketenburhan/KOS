#include <iostream>
#include "Console.h"

namespace Console {
	void Log(const char* msg) {
		std::cout << msg << std::endl;
	}
}