#pragma once

#include <raylib.h>
#include <memory>
#include <game.hpp>
#include <UI/ui_element.hpp>
#include <optional>

class Game;

class GameMenu {
public:

    GameMenu();
    
    virtual void update() = 0;
    virtual void render() = 0;
    bool isActive();

    virtual ~GameMenu() {};

protected:
    bool _is_active;
};

class StartMenu : public GameMenu {
public:
  
    StartMenu(bool& isGameRunning);
    
    ~StartMenu();

    void update() override;

    void render() override;

private:

    bool& _isGameRunning;
    Music _background_music;
    std::optional<Button> _start_button;
    std::optional<Button> _exit_button;
    Texture2D _background;
};


class PauseMenu : public GameMenu {
public:
    void update() override;
    void render() override;

};