#pragma once

#include<functional>

#include "raylib.h"
#include "entity.hpp"

class Interactivable {
public:

    Interactivable(float interactive_radius = 1.0f, const std::function<void*()> & iteract = nullptr);

    void onInteract() const;

    float getInteractiveRadius() const;
    const std::function<void*()> & getInteract() const;

    void setIntaractiveRadius();
    void setInteract(const std::function<void*()> & iteract);

protected:
    float _interactive_radius;
    std::function<void*()> _interact;
};

class InteractiveObject : public Entity, public Interactivable {

    InteractiveObject(float _interactive_radius = 1.0f, const std::function<void*()> & iteract = nullptr);

    bool isPointInRange(const Vector2 & point);

};