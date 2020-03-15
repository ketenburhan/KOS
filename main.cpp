#include <iostream>
#include <string>
#include <regex>
#include "Console/Console.h"

int run(std::string input) {
	std::regex e ("\\b([-_a-zA-Z0-9]+)\\b");
	std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
	std::regex_match (input,sm,e);
	std::cout << "string object with " << sm.size() << " matches\n";

	for (unsigned i=0; i<sm.size(); ++i) {
		std::cout << "[" << sm[i] << "]";
	}
	std::cout << std::endl;
	return 0;
};

int main() {
	Console::Log("Hello, world!\n\n");

	std::string input;

	while (true) {
		input = Console::Getline();

		run(input);
	}
	Console::Wait();
};


class Command {
	Command() {
		
	}
};