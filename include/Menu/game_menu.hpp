#pragma once
#include <raylib.h>
#include <memory>
class GameMenu {
public:

    virtual void handleInput() = 0;
    virtual void renderMenu() = 0;
    
    virtual ~GameMenu() {}; 
};

class StartMenu : public GameMenu {
public:

    void handleInput() override {};
    void renderMenu() override {};

};


class PauseMenu : public GameMenu {
public:
    void handleInput() override;
    void renderMenu() override;
};

