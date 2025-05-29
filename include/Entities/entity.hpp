#pragma once

#include <raylib.h>
#include <vector>
#include <string>

#include "animation_component.hpp"
#include "collidable.hpp"
#include "constants.hpp"

class Entity : public Collidable {
public:

    Entity();

    bool checkCollission(const Collidable& obj);
    void move(const Vector2& dest);
    void move(float x, float y);
    
    void setPosition(const Vector2& position);
    void setPosition(float x, float y);

    const Vector2& getPosition();


    void update();
    void render();

    virtual ~Entity() {};

protected:

    Rectangle _hitbox;
    std::vector<Texture2D> _textures;
    RotationStates _rotation_state;
    Vector2 _position;
    int _velocity;
    bool _isColliadable;
    int _id;
    AnimationComponent _component;
};