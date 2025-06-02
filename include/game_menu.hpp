#pragma once

#include <raylib.h>
#include <UI/ui_element.hpp>

class Game;

class GameMenu {
public:

    GameMenu();
    
    virtual void update() = 0;
    virtual void render() const = 0;
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

    void render() const override;

private:

    bool& _isGameRunning;

    Music _background_music;
    Texture2D tex_story_anim;
    

    Button _start_button;
    Button _exit_button;

    const Button* _selected_button = &_start_button;
    
    struct {
        Texture2D texture;
        float x_pos;
        float y_pos;
    } _arrow;
    
    Texture2D _background;
};


class PauseMenu : public GameMenu {
public:
    void update() override;
    void render() const override;

};