#include <iostream>
#include "Console.h"

namespace Console {
	void Write(const char* msg) {
		std::cout << msg;
	}
	void Write(int msg) {
		std::cout << msg;
	}
	void Log(const char* msg) {
		std::cout << msg << std::endl;
	}
	void Log(int msg) {
		std::cout << msg << std::endl;
	}
	std::string Get() {
		std::string value;
		std::cin >> value;
		return value;
	}
	std::string Getline() {
		std::string value;
		std::getline(std::cin, value);
		return value;
	}
	void Wait() {
		std::cin.get();
	}
}