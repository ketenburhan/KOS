#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

namespace Console {
	template <typename T>
	void Write(T);
	template <typename T>
	void Log(T);
	std::string Get();
	std::string Getline();
	void Wait();
}

#endif