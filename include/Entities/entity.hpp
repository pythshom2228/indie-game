#pragma once

#include <raylib.h>
#include <vector>
#include <string>

#include "animation_component.hpp"
#include "collidable.hpp"
#include "constants.hpp"

class Entity : public Collidable {
public:

    Entity(const std::vector<Texture2D> & textures, const Vector2 & position = {0.0f, 0.0f});

    void move(const Vector2& dest);
    void move(float x, float y);
    void scale(float width, float height);
    
    void setPosition(const Vector2& position);
    void setPosition(float x, float y);

    Vector2 getPosition() const;

    virtual void update() = 0;
    void render() const;


protected:

    std::vector<Texture2D> _textures;
    RotationStates _rotation_state;

    Vector2 _position;
    Vector2 _scale = {1.0f, 1.0f};

    int _velocity;

    bool _isColliadable;
    int _id;

    AnimationComponent _component;
};