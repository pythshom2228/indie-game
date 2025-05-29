#pragma once

#include <raylib.h>
#include <memory>
#include <game.hpp>

class GameMenu {
public:

    virtual void update() = 0;
    virtual void render() = 0;
    bool isActive();

    virtual ~GameMenu() {}; 
private:
    Game* _game;
    bool _isActive;
};

class StartMenu : public GameMenu {
public:
    void update() override;
    void render() override;
};


class PauseMenu : public GameMenu {
public:
    void update() override;
    void render() override;

};

