#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <vector>
#include <iterator>
#include "Console/Console.hpp"

#include "FileSys/FileSys.hpp"


int run(std::string input) {
	//                 "\-([\w\-\_]+)(?:\=([\w\-\_]|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)+)?|[\w\-\_]+|\w+|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\"  
	std::regex e (R"reg(\-([\w\-\_]+)(?:\=([\w\-\_]|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)+)?|[\w\-\_]+|\w+|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)reg");

	std::regex_token_iterator<std::string::iterator> rend;


	std::regex_token_iterator<std::string::iterator> a ( input.begin(), input.end(), e );
	while (a!=rend) std::cout << " [" << *a++ << "]";
	Console::Nextline();
	return 0;
};

int main() {
	std::string _USERNAME ("buran"),
				_DEVICE ("PC"),
				input;

	std::vector<std::string> path = {"home", "Documents", "projects"};
	bool _RUNNING (true);

	while (_RUNNING) {
		Console::Write(_USERNAME + '@' + _DEVICE + ':');
		for (std::string pathnow : path) {
			Console::Write('/' + pathnow);
		}
		Console::Write("-$ ");
		input = Console::Getline();

		run(input);
	}
	Console::Wait();
};


class Command {
	Command() {
		
	}
};