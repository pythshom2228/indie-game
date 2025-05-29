#pragma once
#include "entity.hpp"

class NPC : public Entity {
public:

protected:
    std::string _name;
    std::vector<std::string> _phrases;
};