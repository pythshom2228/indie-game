#pragma once

#include <raylib.h>

#include "entity.hpp"
#include "quest.hpp"

class Player : public Entity {
public:

    Player() = default;

    
    void interact();

private:
    int _hp;
    std::string _name;
    Quest* _current_quest;
};