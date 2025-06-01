#pragma once
#include "raylib.h"

class InteractiveObject {
public:
    InteractiveObject(const Vector2& position, float interactionRadius);
    virtual ~InteractiveObject() = default; // Виртуальный деструктор для корректного удаления наследников

    // Получение позиции и радиуса
    Vector2 getPosition() const;
    float getInteractionRadius() const;

    // Установка позиции и радиуса
    void setPosition(const Vector2& newPosition);
    void setInteractionRadius(float radius);

    // Проверка, находится ли игрок в зоне взаимодействия
    bool isPlayerInRange(const Vector2& playerPosition) const;

    // Виртуальный метод взаимодействия (можно переопределить)
    virtual void onInteract();

protected:
    Vector2 _position;         // Мировая позиция (центр объекта)
    float _interactionRadius;  // Радиус, в котором можно взаимодействовать
};