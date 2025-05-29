#pragma once
#include <raylib.h>
#include "entity.hpp"
#include "quest.hpp"

class Player : Entity {
    
    void render() override;

private:
    int _hp;
    std::string _name;
    Quest* _current_quest;
    Camera2D _camera;
};