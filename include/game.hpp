#pragma once
#include <raylib.h>
#include <game_menu.hpp>
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

    const size_t window_width;
    const size_t wnidow_height;
    const Font font;
    std::unique_ptr<GameMenu> menu;
    Player m_player;
};