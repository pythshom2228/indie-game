#pragma once

#include <raylib.h>
#include <vector>
#include <string>

#include "animation_component.hpp"
#include "collidable.hpp"
#include "constants.hpp"

class Entity : public Collidable {
public:

    Entity(const std::vector<Texture2D> textures, const Vector2 position = {0.0f, 0.0f});

    bool checkCollission(const Collidable& obj);
    void move(const Vector2& dest);
    void move(float x, float y);
    void scale(float width, float height);
    
    void setPosition(const Vector2& position);
    void setPosition(float x, float y);

    const Vector2& getPosition();

    void update();
    void render();

    virtual ~Entity() = default;

protected:

    Rectangle _hitbox;
    std::vector<Texture2D> _textures;
    RotationStates _rotation_state;
    Vector2 _position;
    Vector2 _scale = {0.5f, 0.5f};
    int _velocity;
    bool _isColliadable;
    int _id;
    AnimationComponent _component;
};