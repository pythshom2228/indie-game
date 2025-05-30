#pragma once

#include "entity.hpp"
#include <iostream>

Entity::Entity(const std::vector<Texture2D> & textures, const Vector2 & position)
: _textures(textures), _position(position), _rotation_state(RotationStates::Up) {}

void Entity::move(const Vector2& dest) {
    move(dest.x, dest.y); 
}

void Entity::move(float x, float y) {
    _position.x += x;
    _position.y += y;

    // Обновляем все хитбоксы
    updateHitboxes(x, y);
    
    if (y > 0.0f) {
        _rotation_state = RotationStates::Down;
    } else if (y < 0.0f) {
        _rotation_state = RotationStates::Up;
    }
}

void Entity::updateHitboxes(float x, float y) {
    // Основной хитбокс
    _hitbox.x += x;
    _hitbox.y += y;
    
    // Верхний хитбокс (30% высоты, расположен сверху)
    _up_hitbox.x += x;
    _up_hitbox.y += y; // Смещение вверх
    
    // Нижний хитбокс (30% высоты, расположен снизу)
    _down_hitbox.x += x;
    _down_hitbox.y += y; // Смещение вниз
}

void Entity::scale(float width, float height) {
    _scale.x = height;
    _scale.y = width;
}

void Entity::setPosition(const Vector2& position) {
    setPosition(position.x, position.y);
}

void Entity::setPosition(float x, float y) {
    _position.x = x;
    _position.y = y;
    
    initHitbox();

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

    DrawRectangleLinesEx(
        {_hitbox.x, _hitbox.y, 
        _hitbox.width, _hitbox.height}, 
        3.0f, RED
    );

    DrawRectangleLinesEx(
        {_up_hitbox.x, _up_hitbox.y, 
            _up_hitbox.width, _up_hitbox.height}, 
            3.0f, GREEN
    );

    DrawRectangleLinesEx(
        {_down_hitbox.x, _down_hitbox.y, 
            _down_hitbox.width, _down_hitbox.height}, 
            3.0f, BLUE
    );
    
    // Отладочная точка в центре (можно убрать)
    DrawCircle(_position.x, _position.y, 2.0f, BLUE);


    int x1 = _hitbox.x;
    int y1 = _hitbox.y;

    int x2 = (_hitbox.x + _hitbox.width);
    int y2 = _hitbox.y;

    int x3 = (_hitbox.x + _hitbox.width);
    int y3 = (_hitbox.y + _hitbox.height);

    int x4 = _hitbox.x;
    int y4 = (_hitbox.y + _hitbox.height);

    DrawCircle(x1, y1, 15.0f, GREEN);
    DrawCircle(x2, y2, 15.0f, RED);
    DrawCircle(x3, y3, 15.0f, BLUE);
    DrawCircle(x4, y4, 15.0f, YELLOW);

    int x = _position.x / 256.0f;
    int y = _position.y / 256.0f;

    std::string coord = std::to_string(x) + " " + std::to_string(y);

    DrawText(coord.c_str(), _position.x - 30, _position.y - 170, 50, RED);

}

void Entity::initHitbox() {
    // Основной хитбокс (все тело)
    _hitbox = {
        _position.x - 55.0f, _position.y - 100.0f, 
        110.0f, 210.0f
    };

    //Верхний хитбокс (30% высоты основного хитбокса)
    _up_hitbox = {
        _position.x - 55.0f, _position.y - 100.0f, 
        110.0f, 120.0f
    };
    
    // Нижний хитбокс (30% высоты основного хитбокса)
    _down_hitbox = {
        _position.x - 55.0f, _position.y + 65.0f, 
        110.0f, 50.0f
    };
}
