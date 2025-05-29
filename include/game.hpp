#pragma once
#include <raylib.h>
#include <memory>

#include "player.hpp"
#include "Menu/game_menu.hpp"
#include "world.hpp"
#include "lobby.hpp"

class Game {
public:
    Game();
    
    ~Game() = default;
    
    void start();

private:

    void render();
    void loadWorld(const World& _world);
    void update();
    void pause();

    bool isRunning = false;
    const size_t window_width;
    const size_t window_height;
    std::unique_ptr<GameMenu> menu;
    std::unique_ptr<World> _world;
    Player m_player;

    Camera2D _camera;
};