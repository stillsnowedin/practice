#include "IOManager.h"


bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {
    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }
    
    //seek to end
    file.seekg(0, std::ios::end);
    
    //get the file size
    std::streamoff fileSize = file.tellg();
    
    //seek to beginning
    file.seekg(0, std::ios::beg);
    
    //reduce file size by header bytes if present
    fileSize -= file.tellg();
    
    buffer.resize(fileSize);
    file.read((char*)&buffer[0], fileSize);
    
    file.close();
    return true;
}