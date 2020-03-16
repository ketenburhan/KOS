#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "Console/Console.h"
#include <iterator>

/*
 * 
 * TODO
 * ****
 * 
 * flags
 * command
 * Console types (template)
 */

int run(std::string input) {
	//                         ^\s*([\w\-0-9]+)(?:\s+(\w+|\"(?:[^\"]|\\\")+\"|(?:-\w+(?:=\w+)?)|(?:-\w+(?:=\"(?:[^\"]|\\\")+\")?)|\\[^\\]*\\))*\s*$
	
	//                         ^ \s*([ \w \-0-9]+)(?: \s+( \w+| \       "     (?:[^ \      "     ]|\\ \      "     )+ \      "     |(?:- \w+(?:= \w+)?)|(?:- \w+(?:= \      "     (?:[^ \      "     ]|\\ \      "     )+ \        "     )?)| \ \[^ \ \]* \ \))* \s*$
	// std::regex e (std::string("^\\s*([\\w\\-0-9]+)(?:\\s+(\\w+|\\") + '\"' + "(?:[^\\" + '\"' + "]|\\\\" + '\"' + ")+\\" + '\"' + "|(?:-\\w+(?:=\\w+)?)|(?:-\\w+(?:=\\" + '\"' + "(?:[^\\" + '\"' + "]|\\\\" + '\"' + ")+\\\\" + '\"' + ")?)|\\\\[^\\\\]*\\\\))*\\s*$");
	// std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
	// std::regex_match (input,sm,e);
	// std::cout << "string object with " << sm.size() << " matches\n";

	// for (unsigned i=0; i<sm.size(); ++i) {
	// 	std::cout << "[" << sm[i] << "]";
	// }
	// std::cout << std::endl;
	std::string s ("RegExr21234-w was created by \"gskinner    com\" \"sadfjlk\" and \\is proudly\\ hosted by Media Temple");
	//                         [ \w \- \_]+| \w+| \       "     [^ \      "     ]* \     "     | \ \[^ \ \]* \ \   

	std::regex e (std::string("[\\w\\-\\_]+|\\w+|\\") + '\"' + "[^\\" + '\"' + "]*\\" + '"' + "|\\\\[^\\\\]*\\\\");   // matches words beginning by "sub"

	// default constructor = end-of-sequence:
	std::regex_token_iterator<std::string::iterator> rend;


	// std::regex_token_iterator<std::string::iterator> a ( s.begin(), s.end(), e );
	std::regex_token_iterator<std::string::iterator> a ( input.begin(), input.end(), e );
	while (a!=rend) std::cout << " [" << *a++ << "]";

	return 0;
};

int main() {
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