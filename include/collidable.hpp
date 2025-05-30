#pragma once

#include <raylib.h>

class Collidable {
public:

    Rectangle getHitbox() const;
    Rectangle getUpHitbox() const;
    Rectangle getDownHitbox() const;

    void setHitbox(const Rectangle & hitbox);
    void setUpHitbox(const Rectangle & hitbox);
    void setDownHitbox(const Rectangle & hitbox);

protected:
    Rectangle _hitbox;
    Rectangle _up_hitbox;
    Rectangle _down_hitbox;

};