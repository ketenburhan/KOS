#ifndef FILESYS_HPP_INCLUDED
#define FILESYS_HPP_INCLUDED

#define OK '1'
#define FAIL '2'

class File {
	public:
	std::string name,
				type,
				content;

	File() {}
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
	char create(Folder n) {
		folders.push_back(n);
		return OK;
	}
	char create(File n) {
		files.push_back(n);
		return OK;
	}
	Folder getFolderByPath(Folder from,std::vector<std::string> path) {
		for (std::string pn : path) {
			for (Folder fold : from.folders) {
				if (fold.name == pn) {
					from = fold;
					break;
				}
			}
		}
		return from;
	}
	File getFileByPath(Folder from,std::vector<std::string> path) {
		for (int i = 0; i<path.size()-1; i++) {
			std::string pn = path[i];
			for (Folder fold : from.folders) {
				if (fold.name == pn) {
					from = fold;
					break;
				}
			}
		}
		File mustReturn;
		for (File x : from.files) {
			if (x.name == path[path.size()-1]) {
				mustReturn = x;
			}
		}
		return mustReturn;
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

#endif