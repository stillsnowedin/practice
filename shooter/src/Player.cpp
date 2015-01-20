#include "Player.h"
#include "World.h"
#include "Map.h"
#include "Utility.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

Player::Player(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation)
    : Entity(world, path, position, rotation) {
        setupCamera();
        setupMap();
        parseConfig(path);
}

Player::~Player() {

}

void Player::setupCamera() {
    camera = world->smgr->addCameraSceneNodeFPS();
    //set the nodes position and rotation
    if (camera) {
        camera->setPosition(position);
        camera->setRotation(rotation);
        camera->setFarValue(8000.0f);
    }
    
    //set up the default gun
    irr::scene::IAnimatedMeshMD2 *weapon_mesh = nullptr;
    irr::scene::IAnimatedMeshSceneNode *weapon_node = nullptr;
    
    weapon_mesh = (irr::scene::IAnimatedMeshMD2*)world->smgr->getMesh("../../media/gun.md2");
    if (weapon_mesh == nullptr) return;
    
    weapon_node = world->smgr->addAnimatedMeshSceneNode(weapon_mesh, camera, 10, irr::core::vector3df(0, 0, 0), irr::core::vector3df(-90, -90, 90));
    weapon_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    weapon_node->setMaterialTexture(0, world->driver->getTexture("../../media/gun.jpg"));
    weapon_node->setMD2Animation("idle");
    weapon_node->setLoopMode(true);
    weapon_node->setName("Quake gun");
}

void Player::setupMap() {
    //Get the selector from the map
    if (world->entities["map"].size() == 0) {
        std::cout << " -> Map doesn't exist yet, invalid configuration file" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    //retrieve the map
    Map *map = dynamic_cast<Map*>(world->entities["map"].front());
    
    if (map->selector) {
        irr::scene::ISceneNodeAnimator *anim = world->smgr->createCollisionResponseAnimator(
            map->selector, camera, irr::core::vector3df(30, 50, 30), irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
        camera->addAnimator(anim);
        anim->drop();
    }
}

void Player::parseConfig(const std::string &path) {
    
}
