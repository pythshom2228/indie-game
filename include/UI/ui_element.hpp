#pragma once
#include <raylib.h>
#include <functional>

class Button {
public:

    Button(const Vector2& position, const Texture2D& texture);

    Button(
        const std::function<void()>& action_on_click, const std::function<void()>& action_hover,
        const Vector2& position, const Texture2D& texture);

    void update();

    void render() const;

    void setActions(const std::function<void()>& action_on_click, const std::function<void()>& action_hover);
    
    void setPosition(const Vector2& position);
    void setPosition(float x, float y);

    Vector2 getPosition() const;
    float getWidth() const;
    float getHeight() const;

private:

    bool _isMouseOnButton = false;

    Color _color_state = GRAY;

    std::function<void()> _action_hover;
    std::function<void()> _action_on_click;

    Rectangle _box;
    Texture2D _texture;
};