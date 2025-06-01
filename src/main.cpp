#include <game.hpp>
#include "raylib.h"
#include <iostream>

int main(void) {

    InitWindow(1280, 720, "Game");
//    InitAudioDevice();

    
    Game game;
    
    game.start();

    return 0;
}