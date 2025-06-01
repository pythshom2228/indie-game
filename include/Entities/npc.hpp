#pragma once
#include "entity.hpp"
#include <Interactive/interactivable.hpp>

class NPC : public InteractiveObject {
public:
    
    NPC(const std::array<Texture2D,DIRECTIONS_COUNT>& textures, const Vector2 & position);

    
    void update();

    void render() const;

protected:

    std::string _name;

    std::vector<std::string> _phrases;

};