#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <vector>
#include <iterator>
#include "Console/Console.hpp"

#include "FileSys/FileSys.hpp"




char run(std::string input) {
	//                 "\-([\w\-\_]+)(?:\=([\w\-\_]|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)+)?|[\w\-\_]+|\w+|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\"  
	std::regex e (R"reg(\-([\w\-\_]+)(?:\=([\w\-\_]|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)+)?|[\w\-\_]+|\w+|\"(?:\\\"|[^\"])*\"|\\[^\\]*\\)reg");

	std::regex_token_iterator<std::string::iterator> rend;


	std::regex_token_iterator<std::string::iterator> a ( input.begin(), input.end(), e );
	while (a!=rend) std::cout << " [" << *a++ << "]";
	Console::nl();
	return OK;
};

int main() {

	Folder DISK = Folder(std::string("root"));
	std::string _USERNAME ("buran"),
				_DEVICE ("PC"),
				input;

	std::vector<std::string> path = {"home", "Documents", "projects"};
	bool _RUNNING (true);

	std::cout <<  DISK.createFolder(std::string("Apps")) << std::endl;
	std::vector<std::string> cd {"Apps"};
	std::cout <<  DISK.getFolderByPath(DISK, cd).name << std::endl;
	while (_RUNNING) {
		Console::Write(_USERNAME + '@' + _DEVICE + ':');
		for (std::string pathnow : path) {
			Console::Write('/' + pathnow);
		}
		Console::Write("-$ ");
		input = Console::Getline();

		run(input);
	}
};


class Command {

	Command() {
		
	}
};