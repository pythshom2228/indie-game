#include "game_menu.hpp"

GameMenu::GameMenu() : _is_active(true) {}

bool GameMenu::isActive() {
    return _is_active;
}

StartMenu::StartMenu(bool& isGameRunning) : _isGameRunning(isGameRunning) {
    Sound button_sound = LoadSound(RES_PATH"UI/ButtonPressed.mp3");
    Texture start_button_texture = LoadTexture(RES_PATH"UI/StartButton.png");
    Texture exit_button_texture = LoadTexture(RES_PATH"UI/ExitButton.png");

    _start_button = Button(
        [this, button_sound](){ 
            this->_is_active = false;
            PlaySound(button_sound);
        },
        Vector2{0,0},
        LoadTexture(RES_PATH"UI/StartButton.png")
    );

    _exit_button = Button(
        [this, button_sound]() { 
            this->_isGameRunning = false; 
            PlaySound(button_sound);

        },
        Vector2{0,0},
        LoadTexture(RES_PATH"UI/ExitButton.png")
    );
    
    Button& startb = _start_button.value(); 
    Button& exitb = _exit_button.value();
    
    startb.setPosition(250.0f,190.0f);
    exitb.setPosition(
        startb.getPosition().x,
        startb.getPosition().y + startb.getHeight()
    );

    _background = LoadTexture(RES_PATH"UI/StartMenuBackground.png");
}

void StartMenu::update() {
    _start_button->update();
    _exit_button->update();
}

void StartMenu::render() {
    DrawTexture(_background,0,0,WHITE);

    _start_button->render();
    _exit_button->render();
}

void PauseMenu::update() {

}

void PauseMenu::render() {
    
}