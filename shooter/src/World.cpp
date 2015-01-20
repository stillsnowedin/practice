#include "World.h"
#include "Entity.h"
#include "Player.h"
#include "Item.h"
#include "Zombie.h"
#include "Map.h"
#include "Utility.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

World::World(const std::string &filePath) {
    setupEngine();
    //open file
    std::fstream fin(filePath);
    std::string command;
    
    //insert the entities
    entities.insert(std::make_pair("player", std::vector<Entity*>()));
    entities.insert(std::make_pair("map", std::vector<Entity*>()));
    entities.insert(std::make_pair("zombie", std::vector<Entity*>()));
    entities.insert(std::make_pair("item", std::vector<Entity*>()));
    
    //iterate through lines in the files
    std::cout << "* Constructing World" << std::endl;
    while (std::getline(fin, command)) {
        //create a vector to store the tokens and convert the line to a string stream
        std::vector<std::string> tokens;
        str_to_vec(command, tokens);
        
        if (tokens.size() == 4) {
            std::cout << " -> Entity - Type: " << tokens[0] << " File: " << tokens[1] << " Position: " << tokens[2]
                << " Rotation: " << tokens[3] << std::endl;
        
            //construct the entity with position and rotation
            irr::core::vector3df position(str_to_vec3df(tokens[2]));
            irr::core::vector3df rotation(str_to_vec3df(tokens[3]));
            std::string path = "../../data/";
            path += tokens[1] + ".txt";
            
            //simple dispatcher for each of the valid types
            if (tokens[0] == "player") entities["player"].push_back(new Player(this, path, position, rotation));
            else if (tokens[0] == "map") entities["map"].push_back(new Map(this, path, position, rotation));
            else if (tokens[0] == "zombie") entities["zombie"].push_back(new Zombie(this, path, position, rotation));
            else if (tokens[0] == "item") entities["item"].push_back(new Item(this, path, position, rotation));
        } else {
            std::cout << " -> Entity - Malformed command, ignoring" << std::endl;
        }
    }
    std::cout << "* Finished Constructing World" << std::endl;
}

//set up the device, driver, and scene manager
void World::setupEngine() {
    device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1024, 720));
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    device->getCursorControl()->setVisible(false);
}

void World::run() {
    while (device->run()) {
        //if the window is active, render the scene
        if (device->isWindowActive()) {
            //update entities
            driver->beginScene(true, true, irr::video::SColor(255, 200, 200, 200));
            smgr->drawAll();
            driver->endScene();
        //otherwise just yield the device to spare CPU usage
        } else {
            device->yield();
        }
    }
}