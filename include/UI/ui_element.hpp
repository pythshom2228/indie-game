#pragma once
#include <raylib.h>
#include <functional>

class Button {
public:

    template<class Callable>
    Button(Callable&& action,const Vector2& position, const Texture2D& texture)
    :   _action(std::forward<Callable>(action)), 
        _box(Rectangle{position.x, position.y, texture.width, texture.height}), 
        _texture(texture) 
    {}
    
    void update();

    void render();

    void setPosition(const Vector2& position);
    void setPosition(float x, float y);

    Vector2 getPosition();
    float getWidth();
    float getHeight();

private:
    
    Color _color_state = GRAY;
    std::function<void()> _action;
    Rectangle _box;
    Texture2D _texture;
};