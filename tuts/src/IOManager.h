#ifndef __tuts__IOManager__
#define __tuts__IOManager__

#include <vector>
#include <fstream>

class IOManager {
public:
    static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
    
};

#endif /* defined(__tuts__IOManager__) */
