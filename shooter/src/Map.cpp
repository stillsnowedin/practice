#include "Map.h"
#include "Utility.h"
#include "World.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

Map::Map(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation)
    : Entity(world, path, position, rotation) {
    std::cout << " -> Constructing Map: " << path << std::endl;
    std::fstream fin(path);
    std::string command;
    
    while (std::getline(fin, command)) {
        std::vector<std::string> tokens;
        str_to_vec(command, tokens);
        //if the command type is file then just load the file
        if ((tokens.size() == 3) && (tokens[0] == "file")) {
            std::cout << " -> [map][loading] pkg: " << tokens[1] << " mesh: " << tokens[2] << std::endl;
            loadMap(tokens[1], tokens[2]);
        }
    }
}

Map::~Map() {
}

void Map::loadMap(const std::string &pkgPath, const std::string &bspPath) {
    world->device->getFileSystem()->addFileArchive(pkgPath.c_str());
    irr::scene::IAnimatedMesh *mesh = world->smgr->getMesh(bspPath.c_str());
    
    if (mesh)
        node = world->smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1 << 0);
        
    if (node) {
        node->setPosition(position);
        node->setRotation(rotation);
        selector = world->smgr->createOctreeTriangleSelector(node->getMesh(), node, 128);
        node->setTriangleSelector(selector);
    }
}