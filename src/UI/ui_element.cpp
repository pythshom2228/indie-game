#include "UI/ui_element.hpp"

Button::Button(const Vector2& position, const Texture2D& texture) 
: _box( Rectangle {
        position.x, 
        position.y, 
        static_cast<float>(texture.width), 
        static_cast<float>(texture.height)
    }),
 _texture(texture)
 {}

Button::Button(
        const std::function<void()>& action_on_click, const std::function<void()>& action_hover,
        const Vector2& position, const Texture2D& texture
    ) : Button::Button(position,texture) 
    {
        this->_action_on_click = action_on_click;
        this->_action_hover = action_hover;
    }

void Button::update() {
    
    bool wasOnButton = _isMouseOnButton;

    _isMouseOnButton = CheckCollisionPointRec(
        GetMousePosition(),
        _box 
    );

    _color_state = GRAY;
    
    if(_isMouseOnButton) {
        _color_state = WHITE;
        if(!wasOnButton)
            _action_hover();
                    
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            _action_on_click();
        }
    }
}

void Button::render() {
    DrawTexture(_texture,_box.x,_box.y, _color_state);
}

void Button::setActions(const std::function<void()>& action_on_click, const std::function<void()>& action_hover) {
    this->_action_on_click = action_on_click;
    this->_action_hover = action_hover;
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