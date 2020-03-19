#include <iostream>
#include "Console.h"

namespace Console {
	template <typename T>
	void Write(T msg) {
		std::cout << msg;
	}
	template <typename T>
	void Log(T msg) {
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