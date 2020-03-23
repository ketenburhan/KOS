#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <vector>
#include <iterator>
#include "../Console/Console.hpp"

#include "../FileSys/FileSys.hpp"

#define test(x,y) if(x!=y) e++
int main() {
	int e = 0;
	{
		// DIR
		Directory* DISK = new Directory("disk1");
		createDisk(DISK);
		auto Apps (new Directory("Apps"));
		auto name (new File("name.type","type"));
		DISK->create(Apps);
		DISK->create(name);
		std::vector<std::string> pathnow = {"Apps"};
		auto value1 = Directory::getDirectoryByPath(DISK, pathnow);
		pathnow = {"name.type"};
		auto value2 = Directory::getFileByPath(DISK, pathnow);
		
		test(Apps, value1);
		test(Apps, DISK->getDirectory("Apps"));
		test(name, value2);
		test("disk1", DISK->name);
	}
	
	return e;
}