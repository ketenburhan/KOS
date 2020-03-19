#ifndef CONSOLE_HPP_INCLUDED
#define CONSOLE_HPP_INCLUDED

namespace Console {
	void Write(std::string);
	void Log(std::string);
	std::string Get();
	std::string Getline();
	void Nextline();
	void Wait();
}

#endif