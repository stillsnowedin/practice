#include "World.h"
#include <string>

int main(int argc, char *argv[]) {
    World *world = new World("../../data/world.txt");
    world->run();
    
    return EXIT_SUCCESS;
}