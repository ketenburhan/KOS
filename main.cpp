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
	Directory* DISK = new Directory("root");
	createDisk(DISK);
	Directory* MNT = new Directory("mnt");
	createDisk(MNT);
	DISK->create(new Directory("Apps"));
	DISK->create(new Directory("Documents"));
	DISK->create(new Directory(".cmd"));
	DISK->create(new Directory("Desktop"));
	std::string _USERNAME ("buran"),
				_DEVICE ("PC"),
				input;

	std::vector<std::string> path = {"home", "Documents", "projects"};
	bool _RUNNING (true);

	std::vector<std::string> cd {"Apps"};
	std::cout <<  DISK << std::endl;
	std::cout <<  getDiskByName("root") << std::endl;
	std::cout <<  Directory::getDirectoryByPath(DISK, cd) << std::endl;
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