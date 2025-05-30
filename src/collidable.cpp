#include "collidable.hpp"

Rectangle Collidable::getHitbox()     const { return _hitbox; }
Rectangle Collidable::getUpHitbox()   const { return _up_hitbox; }
Rectangle Collidable::getDownHitbox() const { return _down_hitbox; }

void Collidable::setHitbox(const Rectangle & hitbox) {
    _hitbox = hitbox;
}

void Collidable::setDownHitbox(const Rectangle &hitbox) {
    _down_hitbox = hitbox;
}

void Collidable::setUpHitbox(const Rectangle &hitbox) {
    _up_hitbox = hitbox;
}
