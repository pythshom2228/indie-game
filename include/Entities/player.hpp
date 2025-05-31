#pragma once

#include <raylib.h>

#include "entity.hpp"
#include "quest.hpp"
#include "UI/hud.hpp"

class Player : public Entity {
public:

    Player();

    Player(const std::vector<Texture2D> _textures, const std::string & name,const Vector2 & position, int hp = 3);
    void update() override;
    
    void setName(const std::string & name);
    void setQuest(Quest& quest);
    void setHp(int hp);
    

    const std::string & getName() const;
    const Quest * getQuest() const;
    int getHp() const;

    void interact();

private:
    int _hp;
    std::string _name;
    Quest* _current_quest;
};