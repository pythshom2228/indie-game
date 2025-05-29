#pragma once
#include <raylib.h>
#include <Menu/game_menu.hpp>
#include <memory>
#include <player.hpp>

class Game {
public:
    Game();
    ~Game() = default;
    
    void start();

private:

    void run();
    void pause();

    bool isRunning = false;
    const size_t window_width;
    const size_t window_height;
    std::unique_ptr<GameMenu> menu;
    Player m_player;

    Camera2D _camera;
};