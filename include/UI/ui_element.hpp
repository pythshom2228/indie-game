#pragma once
#include <raylib.h>
#include <functional>
#include <memory>

class UIElement {
public:

    UIElement(const Vector2& position, const Vector2& size, const std::shared_ptr<Texture2D>& texture); 

    ~UIElement() = default;

    virtual void render() const = 0;

protected:

    NPatchInfo _npatch;

    Vector2 _position;

    Vector2 _size;

    std::shared_ptr<Texture2D> _texture;

};
