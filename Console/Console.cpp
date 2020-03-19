#include <iostream>
#include "Console.hpp"

namespace Console {
	void Write(std::string msg) {
		std::cout << msg;
	}
	void Log(std::string msg) {
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
	void Nextline() {
		std::cout << std::endl;
	}
	void Wait() {
		std::cin.get();
	}
}