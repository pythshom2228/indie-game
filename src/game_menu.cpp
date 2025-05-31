#include "game_menu.hpp"

GameMenu::GameMenu() : _is_active(true) {}

bool GameMenu::isActive() {
    return _is_active;
}



StartMenu::StartMenu(bool& isGameRunning) : _isGameRunning(isGameRunning) {
    Sound button_hover_sound = LoadSound(RES_PATH"UI/ButtonPressed.mp3");
    const Texture& start_button_texture = LoadTexture(RES_PATH"UI/StartButton.png");
    const Texture& exit_button_texture = LoadTexture(RES_PATH"UI/ExitButton.png");

    _start_button = Button(Vector2{0,0}, start_button_texture);

    _exit_button = Button(Vector2{0,0}, exit_button_texture);
    
    Button& startb_r = _start_button.value(); 
    Button& exitb_r = _exit_button.value();
    
    startb_r.setActions(
        [this]() {
            this->_is_active = false;
        },
        [this,button_hover_sound]() {
            PlaySound(button_hover_sound);
        }
    );
    exitb_r.setActions(
        [this]() {
            this->_isGameRunning = false;
        },
        [this,button_hover_sound]() {
            PlaySound(button_hover_sound);
        }
    );

    startb_r.setPosition(250.0f,190.0f);
    exitb_r.setPosition(
        startb_r.getPosition().x,
        startb_r.getPosition().y + startb_r.getHeight()
    );

    _background = LoadTexture(RES_PATH"UI/StartMenuBackground.png");
//StartMenuBackgroundMusic.mp3
    //_background_music = LoadMusicStream(RES_PATH"UI/StartMenuBackgroundMusic.mp3");
    //_background_music.looping = true;
    
    //    PlayMusicStream(_background_music);
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

StartMenu::~StartMenu() {
    //StopMusicStream(_background_music);
}



void PauseMenu::update() {

}

void PauseMenu::render() {
    
}