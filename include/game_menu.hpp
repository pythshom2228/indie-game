#pragma once
#include <raylib.h>

class GameMenu {
public:
    GameMenu(const Font& font) : game_font(font) {}
    virtual void handleInput();
    virtual void renderMenu();
    const Font& game_font ;
    
    virtual ~GameMenu() {}; 
};

class StartMenu : public GameMenu {
public:


    void handleInput() override;
    void renderMenu() override;

};


class PauseMenu : public GameMenu {
public:
    void handleInput() override;
    void renderMenu() override;
};

