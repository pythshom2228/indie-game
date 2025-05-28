#pragma once
#include <raylib.h>
#include <game_menu.h>
#include <memory>
#include <player.h>

class game {
public:
    game();
    ~game() = default;
    
    void start();

private:

    void run();
    void pause();

    const size_t window_width;
    const size_t wnidow_height;
    const Font font;
    std::unique_ptr<game_menu> menu;
    player m_player;
};