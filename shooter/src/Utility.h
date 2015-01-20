#ifndef shooter_Utility_h
#define shooter_Utility_h

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

static inline void str_to_vec(const std::string &str, std::vector<std::string> &vec) {
    std::istringstream iss(str);
    //split by space and copy backwards into the vector
    std::copy (std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string>>(vec));
}

static inline irr::core::vector3df str_to_vec3df(const std::string &str) {
    std::vector<float> vec;
    std::stringstream ss(str);
    float elem;
    
    while (ss >> elem) {
        vec.push_back(elem);
        if (ss.peek() == ',') ss.ignore();
    }
    
    if (vec.size() == 3) {
        return irr::core::vector3df(vec[0], vec[1], vec[2]);
    }
    
    return irr::core::vector3df();
}
#endif
