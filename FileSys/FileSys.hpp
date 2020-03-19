#ifndef FILESYS_HPP_INCLUDED
#define FILESYS_HPP_INCLUDED

class File;
class Folder;
Folder* createFolder(std::string);
File* createFile(std::string, std::string, std::string);

#endif