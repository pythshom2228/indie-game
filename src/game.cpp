#include <game.hpp>
#include <iostream>
#include "player.hpp"
#include <raymath.h>

Game::Game()
:   window_width(GetScreenWidth()) 
    , window_height(GetScreenHeight())
    , _menu(std::make_unique<StartMenu>(_isRunning)) {
    SetTargetFPS(120);

    _camera = {0};
    _camera.offset = {static_cast<float>(window_width) / 2, static_cast<float>(window_height) / 2}; 
    _camera.target = {0, 0};
    _camera.rotation = 0.0f;  
    _camera.zoom = 1.0f;      
}

void Game::start() {

    _world.loadFromFile("dogWorldSecond.tmx");
    _world.setPlayer(&_player);
    _player.setPosition(200.0f, 200.0f);

    while(!WindowShouldClose() && _isRunning) {
        update();
        render();
    }

    CloseWindow();
}

void Game::update() {

    if(_menu->isActive()) {
        _menu->update();
        _menu->render();

    }
    else {
        _world.update();

        playerHandleInput();


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
}
//
void Game::playerHandleInput() {
    if (IsKeyDown(KEY_A)) 
    {
        _player.move(-3.0f, 0.0f);

        Rectangle hitbox = _player.getHitbox();

        int x1 = hitbox.x / 256.0f;
        int y1 = hitbox.y / 256.0f;

        int x2 = (hitbox.x + hitbox.width) / 256.0f;
        int y2 = hitbox.y / 256.0f;

        int x3 = (hitbox.x + hitbox.width) / 256.0f;
        int y3 = (hitbox.y + hitbox.height) / 256.0f;

        int x4 = hitbox.x / 256.0f;
        int y4 = (hitbox.y + hitbox.height) / 256.0f;

        std::cout << "____________________________________________\n";
        std::cout << "x1: " << x1 << " y1: " << y1 << '\n';
        std::cout << "x2: " << x2 << " y2: " << y2 << '\n';
        std::cout << "x3: " << x3 << " y3: " << y3 << '\n';
        std::cout << "x4: " << x4 << " y4: " << y4 << '\n';

        if 
        (//
            _world.getTile(x1, y1).getTileClass() == TileClass::Wall ||
            _world.getTile(x2, y2).getTileClass() == TileClass::Wall ||
            _world.getTile(x3, y3).getTileClass() == TileClass::Wall ||
            _world.getTile(x4, y4).getTileClass() == TileClass::Wall
        ) 
        {
            _player.setPosition(_player.getPosition().x + 3.0f, _player.getPosition().y);
        }
    }
    if (IsKeyDown(KEY_D)) 
    {
        _player.move(3.0f, 0.0f);

        Rectangle hitbox = _player.getHitbox();

        int x1 = hitbox.x / 256.0f;
        int y1 = hitbox.y / 256.0f;

        int x2 = (hitbox.x + hitbox.width) / 256.0f;
        int y2 = hitbox.y / 256.0f;

        int x3 = (hitbox.x + hitbox.width) / 256.0f;
        int y3 = (hitbox.y + hitbox.height) / 256.0f;

        int x4 = hitbox.x / 256.0f;
        int y4 = (hitbox.y + hitbox.height) / 256.0f;

        std::cout << "____________________________________________\n";
        std::cout << "x1: " << x1 << " y1: " << y1 << '\n';
        std::cout << "x2: " << x2 << " y2: " << y2 << '\n';
        std::cout << "x3: " << x3 << " y3: " << y3 << '\n';
        std::cout << "x4: " << x4 << " y4: " << y4 << '\n';

        if 
        (
            _world.getTile(x1, y1).getTileClass() == TileClass::Wall ||//
            _world.getTile(x2, y2).getTileClass() == TileClass::Wall ||//
            _world.getTile(x3, y3).getTileClass() == TileClass::Wall ||//
            _world.getTile(x4, y4).getTileClass() == TileClass::Wall
        ) 
        {
            _player.setPosition(_player.getPosition().x - 3.0f, _player.getPosition().y);
        }
    }
    if (IsKeyDown(KEY_W)) 
    {
        _player.move(0.0f, -3.0f);
        
        Rectangle hitbox = _player.getHitbox();

        int x1 = hitbox.x / 256.0f;
        int y1 = hitbox.y / 256.0f;

        int x2 = (hitbox.x + hitbox.width) / 256.0f;
        int y2 = hitbox.y / 256.0f;

        int x3 = (hitbox.x + hitbox.width) / 256.0f;
        int y3 = (hitbox.y + hitbox.height) / 256.0f;

        int x4 = hitbox.x / 256.0f;
        int y4 = (hitbox.y + hitbox.height) / 256.0f;

        std::cout << "____________________________________________\n";
        std::cout << "x1: " << x1 << " y1: " << y1 << '\n';
        std::cout << "x2: " << x2 << " y2: " << y2 << '\n';
        std::cout << "x3: " << x3 << " y3: " << y3 << '\n';
        std::cout << "x4: " << x4 << " y4: " << y4 << '\n';

        if 
        (
            _world.getTile(x1, y1).getTileClass() == TileClass::Wall ||
            _world.getTile(x2, y2).getTileClass() == TileClass::Wall ||
            _world.getTile(x3, y3).getTileClass() == TileClass::Wall ||
            _world.getTile(x4, y4).getTileClass() == TileClass::Wall
        ) 
        {
            _player.setPosition(_player.getPosition().x, _player.getPosition().y + 3.0f);
        }
    }
    if (IsKeyDown(KEY_S)) 
    {
        _player.move(0.0f, 3.0f);
        
        Rectangle hitbox = _player.getHitbox();

        int x1 = hitbox.x / 256.0f;
        int y1 = hitbox.y / 256.0f;

        int x2 = (hitbox.x + hitbox.width) / 256.0f;
        int y2 = hitbox.y / 256.0f;

        int x3 = (hitbox.x + hitbox.width) / 256.0f;
        int y3 = (hitbox.y + hitbox.height) / 256.0f;

        int x4 = hitbox.x / 256.0f;
        int y4 = (hitbox.y + hitbox.height) / 256.0f;

        std::cout << "____________________________________________\n";
        std::cout << "x1: " << x1 << " y1: " << y1 << '\n';
        std::cout << "x2: " << x2 << " y2: " << y2 << '\n';
        std::cout << "x3: " << x3 << " y3: " << y3 << '\n';
        std::cout << "x4: " << x4 << " y4: " << y4 << '\n';

        if 
        (
            _world.getTile(x1, y1).getTileClass() == TileClass::Wall ||
            _world.getTile(x2, y2).getTileClass() == TileClass::Wall ||
            _world.getTile(x3, y3).getTileClass() == TileClass::Wall ||
            _world.getTile(x4, y4).getTileClass() == TileClass::Wall
        ) 
        {
            _player.setPosition(_player.getPosition().x, _player.getPosition().y - 3.0f);
        }
    }
}

void Game::render() {
    BeginDrawing();
    ClearBackground(WHITE);

    if(_menu->isActive()) {
        _menu->render();
    }
    else {
        BeginMode2D(_camera);

            _world.render(); 
        
        EndMode2D();

    }
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