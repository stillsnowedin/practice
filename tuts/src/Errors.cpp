#include "Errors.h"

void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    SDL_Quit();
    exit(99);
}