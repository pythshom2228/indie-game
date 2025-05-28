#pragma once
#include <raylib.h>

class game_menu {
public:
    game_menu(const Font& font) : game_font(font) {}
    virtual void handleInput();
    virtual void renderMenu();
    const Font& game_font ;
    
    virtual ~game_menu() {}; 
};

class start_menu : public game_menu {
public:

    start_menu() {}
    void handleInput() override;
    void renderMenu() override;

};


class pause_menu : public game_menu {
public:
    void handleInput() override;
    void renderMenu() override;
};

