#include "Zombie.h"

Zombie::Zombie(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation)
    : Entity(world, path, position, rotation) {
    
}

Zombie::~Zombie() {

}