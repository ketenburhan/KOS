#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "Console/Console.h"
#include <iterator>


int run(std::string input) {

	//                 "\-([\w\-\_]+)(?:\=([\w\-\_]|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)+)?|[\w\-\_]+|\w+|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\"  
	std::regex e (R"reg(\-([\w\-\_]+)(?:\=([\w\-\_]|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)+)?|[\w\-\_]+|\w+|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)reg");

	std::regex_token_iterator<std::string::iterator> rend;


	std::regex_token_iterator<std::string::iterator> a ( input.begin(), input.end(), e );
	while (a!=rend) std::cout << " [" << *a++ << "]";

	return 0;
};

int main() {
	std::string input;
	bool _RUNNING (false);

	while (_RUNNING) {
		input = Console::Getline();

		run(input);
	}
	Console::Wait();
};


class Command {
	Command() {
		
	}
};