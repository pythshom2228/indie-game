#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game()
: window_width(GetScreenWidth()), window_height(GetScreenHeight()) {
    SetTargetFPS(120);
    
        // Инициализация камеры
    _camera = {0};
    _camera.offset = {static_cast<float>(window_width) / 2, static_cast<float>(window_height) / 2}; // Центр камеры
    _camera.target = {0, 0}; // Начальная позиция (обновится в update())
    _camera.rotation = 0.0f;  // Без вращения
    _camera.zoom = 1.0f;      // Стандартный масштаб
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

    _world.update();

    Vector2 playerPos = _player.getPosition();
    _camera.target.x = Lerp(_camera.target.x, playerPos.x, 0.05f);
    _camera.target.y = Lerp(_camera.target.y, playerPos.y, 0.05f);

    if (IsKeyDown(KEY_UP)) {
        _camera.zoom += 0.01f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        _camera.zoom -= 0.01f;
    }

}

void Game::render() {
    BeginDrawing();
    ClearBackground(WHITE);


    BeginMode2D(_camera);

        _world.render(); 
    
    EndMode2D();

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