#pragma once

#include "entity.hpp"

Entity::Entity(const std::vector<Texture2D> textures, const Vector2 position)
: _textures(textures), _position(position), _rotation_state(RotationStates::Up) {

}

bool Entity::checkCollission(const Collidable& obj) {
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

void Entity::scale(float width, float height) {
    _scale.x *= height;
    _scale.y *= width;
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
    Texture2D texture = _textures[_rotation_state];

    DrawTexturePro(
        texture,
        {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)}, 
        {_position.x, _position.y, texture.width * _scale.x, texture.height * _scale.y}, 
        {0.0f, 0.0f}, 0.0f, WHITE
    );
}
