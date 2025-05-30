#pragma once
#include <raylib.h>
#include <memory>

#include "player.hpp"
#include "game_menu.hpp"
#include "world.hpp"

class Game {
public:
    Game();
    
    ~Game() = default;
    
    void start();

private:

    void render();
    void loadWorld(const std::string& _name);
    void update();
    void pause();
    
    void playerHandleInput();
    bool checkCollisionWithWorld(const Rectangle &rect) const;
    bool isSolidTile(int tileId) const;

    bool isRunning = false;
    const size_t window_width;
    const size_t window_height;
    std::unique_ptr<GameMenu> _menu;

    
    World _world;
    
    Player _player;

    Camera2D _camera;
};