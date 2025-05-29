#pragma once

#include "entity.hpp"



bool checkCollission(const Collidable& obj) {
    return false;
}

void Entity::move(const Vector2& dest) {
    _position.x += dest.x;
    _position.y += dest.y;
}

void Entity::move(float x, float y) {
    _position.x += x;
    _position.y += y;
}

void Entity::setPosition(const Vector2& position) {
    _position = position;
}

void Entity::setPosition(float x, float y) {
    _position.x = x;
    _position.y = y;
}

const Vector2& Entity::getPosition() {
    return _position;
}

void update() {

}

void Entity::render() {
    DrawTexture(_textures[_rotation_state], _position.x, _position.y, WHITE);
}
