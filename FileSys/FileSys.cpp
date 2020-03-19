#include <vector>
#include <string>
#include "FileSys.hpp"

class File {
	public:
	std::string name,
				type,
				content;

	File(std::string n, std::string t, std::string c) {
		name = n;
		type = t;
		content = c;
	}
};
class Folder {
	public:
	std::string name;
	std::vector<Folder> folders;
	std::vector<File> files;

	Folder(std::string n) {
		name = n;
	}
	char createFolder(Folder n) {
		folders.push_back(n);
		return '1';
	}
	char createFolder(File n) {
		files.push_back(n);
		return '1';
	}
};

Folder* createFolder(std::string name) {
	if (name.find('.')!=std::string::npos) {
		return new Folder(name);
	}
	return NULL;
}
File* createFile(std::string name, std::string type, std::string content) {
	return new File(name, type, content);
}


Folder DISK (std::string("root"));