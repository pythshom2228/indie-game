#include <game.hpp>
#include <iostream>

Game::Game()
: window_width(800), window_height(800) {
    SetTargetFPS(120);
}

void Game::start() {
    InitWindow(window_width,window_height,"Game");

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