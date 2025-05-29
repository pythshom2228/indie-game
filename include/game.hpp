#pragma once
#include <raylib.h>
#include <memory>

#include "player.hpp"
#include "game_menu.hpp"
#include "world.hpp"
#include "lobby.hpp"

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

    bool isRunning = false;
    const size_t window_width;
    const size_t window_height;
    std::unique_ptr<GameMenu> _menu;

    
    std::vector<World> _worlds;
    std::vector<World>::iterator _currentWorld;
    
    Player _player;

    Camera2D _camera;
};