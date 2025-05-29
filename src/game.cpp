#include <game.hpp>
#include <iostream>

Game::Game()
: window_width(1920), window_height(1080) {
    SetTargetFPS(120);

    _worlds.push_back(World("resources/worlds/old_world.tmx",&_player));
    _worlds.push_back(World("resources/worlds/lobby.tmx",&_player));
    _worlds.push_back(World("resources/worlds/dog_world.tmx",&_player));
    _worlds.push_back(World("resources/worlds/maze_world.tmx",&_player));
    _worlds.push_back(World("resources/worlds/machine_world.tmx",&_player)); 
}

void Game::start() {
    InitWindow(window_width,window_height,"Game");
    

    this->_menu = std::make_unique<StartMenu>();

    _world = std::make_unique<World>("dogWorld.tmx");

    bool isRunning = false;
    while(!WindowShouldClose()) {
        update();
        render();
    }

    CloseWindow();
}

void Game::update() {
    if(_menu->isActive()) {
        _menu->update();
    }
    else {
        _currentWorld->update();        
    }

}

void Game::render() {
    BeginDrawing();
    ClearBackground(WHITE);
    if(_menu->isActive()) {
        _menu->render();
    }
    else {
        _currentWorld->render();
    }

    EndDrawing();
}

void Game::loadWorld(const std::string& _name) {
    for(auto world = _worlds.begin(); world < _worlds.end(); world++) {
        if(world->getName() == _name) {
            _currentWorld = world; 
            return;
        }
    }
}