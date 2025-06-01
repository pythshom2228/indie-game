#include "interactivable.hpp"

#include <raymath.h>



Interactivable::Interactivable(float interactive_radius, const std::function<void*()> & interact)
: _interactive_radius(interactive_radius), _interact(interact)  {}

void Interactivable::onInteract() const {
    _interact();
}

float Interactivable::getInteractiveRadius()                 const { return _interactive_radius; }
const std::function<void*()> & Interactivable::getInteract() const { return _interact; }

void Interactivable::setIntaractiveRadius(float interactiveRadius) { 
    _interactive_radius = interactiveRadius; 
}

void Interactivable::setInteract(const std::function<void*()> & interact) {
    _interact = interact;
}

InteractiveObject::InteractiveObject(const std::array<Texture2D, DIRECTIONS_COUNT> & textures, float interactive_radius, const std::function<void*()> & interact)
: Interactivable(_interactive_radius, interact), Entity(textures) {}

bool InteractiveObject::isPointInRange(const Vector2 & point) {
    Vector2 direction = {
        point.x - _position.x,
        point.y - _position.y
    };
    
    float distance_squared = direction.x * direction.x + direction.y * direction.y;
    float radius_squared = _interactive_radius * _interactive_radius;

    return distance_squared <= radius_squared;
}