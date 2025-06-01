#include "interactiveObject.hpp"
#include <raymath.h>

InteractiveObject::InteractiveObject(const Vector2& position, float interactionRadius) 
    : _position(position), _interactionRadius(interactionRadius) {}

Vector2 InteractiveObject::getPosition() const { return _position; }
float InteractiveObject::getInteractionRadius() const { return _interactionRadius; }

void InteractiveObject::setPosition(const Vector2& newPosition) { _position = newPosition; }
void InteractiveObject::setInteractionRadius(float radius) { _interactionRadius = radius; }

bool InteractiveObject::isPlayerInRange(const Vector2& playerPosition) const {
    return Vector2Distance(playerPosition, _position) <= _interactionRadius;
}

void InteractiveObject::onInteract() {
    TraceLog(LOG_INFO, "Base interact() called at (%.2f, %.2f)", _position.x, _position.y);
}