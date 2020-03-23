#ifndef FILESYS_HPP_INCLUDED
#define FILESYS_HPP_INCLUDED

#define OK '1'
#define FAIL '2'

class File {
	public:
	std::string name,
				type,
				content;
	template <typename T1, typename T2> File(T1 n, T2 t) {
		name = n;
		type = t;
	}
	template <typename T1, typename T2, typename T3> File(T1 n, T2 t, T3 c) {
		name = n;
		type = t;
		content = c;
	}
};
class Directory {
	public:
	std::string name;
	std::vector<Directory*> directories;
	std::vector<File*> files;
	template <typename T> Directory(T n) {
		name = n;
	}
	char create(Directory* n) {
		directories.push_back(n);
		return OK;
	}
	char create(File* n) {
		files.push_back(n);
		return OK;
	}
	Directory* getDirectory(std::string name) {
		for (Directory* dir : directories) {
			if (dir->name == name) {
				return dir;
			}
		}
		return NULL;
	}
	static Directory* getDirectoryByPath(Directory* from, std::vector<std::string> path) {
		for (std::string pn : path) {
			for (Directory* fold : from->directories) {
				if (fold->name == pn) {
					from = fold;
					break;
				}
			}
		}
		return from;
	}
	static File* getFileByPath(Directory* from, std::vector<std::string>& path) {
		for (unsigned i = 0; i<path.size()-1; i++) {
			std::string pn = path[i];
			for (Directory* fold : from->directories) {
				if (fold->name == pn) {
					from = fold;
					break;
				}
			}
		}
		File* mustReturn;
		for (File* x : from->files) {
			if (x->name == path[path.size()-1]) {
				mustReturn = x;
			}
		}
		return mustReturn;
	}
};

std::vector<Directory*> _DISKS;

char createDisk(Directory* newDisk) {
	_DISKS.push_back(newDisk);
	return OK;
}
char removeDisk(Directory* newDisk) {
	for (unsigned i = 0; i<_DISKS.size(); i++) {
		if (newDisk == _DISKS[i]) {
			_DISKS.erase(_DISKS.begin()+i);
			return OK;
		}
	}
	return FAIL;
}

Directory* getDiskByName(std::string name) {
	for (Directory* disk : _DISKS) {
		if (disk->name == name) {
			return disk;
		}
	}
	return NULL;
}


char createToPath(std::string name, Directory* dir) {
	dir->create(new Directory(name));
	return OK;
}
char createToPath(std::string name, std::string type, Directory* dir) {
	dir->create(new File(name, type));
	return OK;
}
char createToPath(std::string name, Directory*& disk, std::vector<std::string> path) {
	Directory* dir = Directory::getDirectoryByPath(disk, path);
	dir->create(new Directory(name));
	return OK;
}
char createToPath(std::string name, std::string type, Directory*& disk, std::vector<std::string> path) {
	Directory* dir = Directory::getDirectoryByPath(disk, path);
	dir->create(new File(name, type));
	return OK;
}
#endif