#pragma once
#include <raylib.h>

class Collidable {
public:

    bool checkCollission(const Collidable& obj);

protected:
    Rectangle _hitbox;
};