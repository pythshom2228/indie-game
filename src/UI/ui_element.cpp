#include "UI/ui_element.hpp"

void Button::update() {
    bool isMouseOnButton = CheckCollisionPointRec(
        GetMousePosition(),
        _box 
    );
    _color_state = GRAY;
    if(isMouseOnButton) {
        _color_state = WHITE;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            _action();
        }
    }
}

void Button::render() {
    DrawTexture(_texture,_box.x,_box.y, _color_state);
}

void Button::setPosition(const Vector2& position) {
    _box.x = position.x;
    _box.y = position.y;
}

void Button::setPosition(float x, float y) {
    _box.x = x;
    _box.y = y;
}

Vector2 Button::getPosition() {
    return Vector2 {_box.x,_box.y};
}

float Button::getWidth() {
    return _box.width;
}

float Button::getHeight() {
    return _box.height;
}