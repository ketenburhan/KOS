#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

namespace Console {
	void Write(const char*);
	void Write(int);
	void Log(const char*);
	void Log(std::string);
	void Log(int);
	std::string Get();
	std::string Getline();
	void Wait();
}

#endif