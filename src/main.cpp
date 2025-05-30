#include <game.hpp>
#include "raylib.h"

int main(void) {

    InitWindow(1920, 1080, "La");

    Game game;
    
    game.start();

    return 0;
}