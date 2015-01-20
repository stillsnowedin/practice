#include "Entity.h"
#include "World.h"

Entity::Entity(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation)
    : world(world), path(path), position(position), rotation(rotation) {
        
}

Entity::~Entity() {

}

void Entity::update() {

}