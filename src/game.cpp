#include <game.hpp>
#include <iostream>

Game::Game()
: window_width(1920), window_height(1080) {
    SetTargetFPS(120);
}

void Game::start() {
    InitWindow(window_width,window_height,"Game");

    _world = std::make_unique<World>("dogWorld.tmx");

    bool isRunning = false;
    while(!WindowShouldClose()) {
        
        update();
        render();

    }

    CloseWindow();
}

void Game::update() {
    
    _world->update();

}

void Game::render() {
    BeginDrawing();
    ClearBackground(WHITE);

    _world->render();

    EndDrawing();
}