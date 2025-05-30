#pragma once

#include "entity.hpp"
#include <iostream>

Entity::Entity(const std::vector<Texture2D> & textures, const Vector2 & position)
: _textures(textures), _position(position), _rotation_state(RotationStates::Up) {

    _hitbox =  {_position.x, _position.y, 130.0f, 220.0f};
}

void Entity::move(const Vector2& dest) {
    _position.x += dest.x;
    _position.y += dest.y;
    _hitbox.x = _position.x;
    _hitbox.y = _position.y;

    if (dest.y > 0.0f) { 
        _rotation_state = RotationStates::Down;
    } else {
        _rotation_state = RotationStates::Up;
    }
}

void Entity::move(float x, float y) {
    _position.x += x;
    _position.y += y;
    _hitbox.x = _position.x;
    _hitbox.y = _position.y;

    if (y > 0.0f) {
        _rotation_state = RotationStates::Down;
    } else {
        _rotation_state = RotationStates::Up;
    }
}

void Entity::scale(float width, float height) {
    _scale.x = height;
    _scale.y = width;
}

void Entity::setPosition(const Vector2& position) {
    _position = position;
}

void Entity::setPosition(float x, float y) {
    _position.x = x;
    _position.y = y;
}

Vector2 Entity::getPosition() const {
    return _position;
}

void update() {
    // Потом
}

void Entity::render() const {
    size_t texture_index = static_cast<size_t>(_rotation_state);
    
    Texture2D texture = _textures[texture_index];
    
    // Рассчитываем смещение, чтобы текстура рисовалась от центра
    Rectangle source_rect = {
        0.0f, 0.0f,                       // Начало текстуры (x, y)
        (float)texture.width,              // Ширина исходной текстуры
        (float)texture.height              // Высота исходной текстуры
    };
    
    Rectangle dest_rect = {
        _position.x,                       // Центр по X
        _position.y,                       // Центр по Y
        texture.width * _scale.x,          // Ширина с масштабом
        texture.height * _scale.y          // Высота с масштабом
    };
    
    Vector2 origin = {
        (texture.width * _scale.x) / 2,    // Центр по X
        (texture.height * _scale.y) / 2    // Центр по Y
    };
    
    // Рисуем текстуру с центром в _position
    DrawTexturePro(
        texture,
        source_rect,
        dest_rect,
        origin,
        0.0f,                              // Угол поворота (если нужно)
        WHITE                              // Цвет (можно добавить поле)
    );
    DrawRectangleLinesEx(_hitbox, 3.0f, RED);
    
    // Отладочная точка в центре (можно убрать)
    DrawCircle(_position.x, _position.y, 2.0f, BLUE);

}
