#pragma once
#include "entity.hpp"

class NPC : Entity {
public:
    void render() override;

private:
    std::string _name;
    std::vector<std::string> _phrases;
};