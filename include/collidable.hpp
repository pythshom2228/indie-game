#pragma once

#include <raylib.h>

class Collidable {
public:

    bool checkCollission(const Collidable& obj);

    const Rectangle & getHitbox() const;

    void setHitbox(const Rectangle & hitbox);

protected:
    Rectangle _hitbox;
};