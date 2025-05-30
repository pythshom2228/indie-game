#include <game.hpp>
#include <iostream>
#include "player.hpp"

Game::Game()
: window_width(1920), window_height(1080) {
    SetTargetFPS(120);
    
}

void Game::start() {

    _world.loadFromFile("dogWorld.tmx");
    _world.setPlayer(&_player);
    


    bool isRunning = false;
    while(!WindowShouldClose()) {
        update();
        render();
    }

    CloseWindow();
}

void Game::update() {
    // if(_menu->isActive()) {
    //     _menu->update();
    // }
    // else {
    //     _world.update();        
    // }

    _world.update();

}

void Game::render() {
    BeginDrawing();
    ClearBackground(WHITE);

    _world.render();

    EndDrawing();
}

void Game::loadWorld(const std::string& _name) {
    // for(auto world = _worlds.begin(); world < _worlds.end(); world++) {
    //     if(world->getName() == _name) {
    //         _currentWorld = world; 
    //         return;
    //     }
    // }
}