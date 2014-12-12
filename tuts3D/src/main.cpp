//
//  main.cpp
//  tuts3D
//
//  Created by Kathryn on 12/9/14.
//  Copyright (c) 2014 stillsnowedin. All rights reserved.
//

#include <iostream>
#include "vector3d.h"

int main(int argc, const char * argv[]) {
    vector3d vec1;
    vector3d vec2(1, 2, 3);
    vector3d vec3(6, 5, 4);
    std::cout << vec1 << vec2;
    std::cout << vec2.length() << std::endl;
    vec2.normalize();
    std::cout << vec2;
    
    vector3d vec23 = vec2 + vec3;
    std::cout << vec23;
    vec23 += vec2;
    std::cout << vec23;
    
    return 0;
}
