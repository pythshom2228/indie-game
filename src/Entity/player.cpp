#include "player.hpp"

Player::Player() 
: Entity({}), _name("Renat"), _hp(3), _current_quest(nullptr) {
    _textures.push_back(LoadTexture(RES_PATH"player/walkUpFirst.png"));
    _textures.push_back(LoadTexture(RES_PATH"player/walkUpFirst.png"));
    _textures.push_back(LoadTexture(RES_PATH"player/walkDownFirst.png"));
    _textures.push_back(LoadTexture(RES_PATH"player/walkDownFirst.png"));

    scale(0.15f, 0.15f);
}

Player::Player(const std::vector<Texture2D> _textures, const std::string & name,const Vector2 & position, int hp) 
: Entity(_textures, position), _name(name), _hp(hp), _current_quest(nullptr) {}

void Player::update() {

    if (IsKeyDown(KEY_A)) 
    {
        move(-3.0f, 0.0f);
    }
    if (IsKeyDown(KEY_D)) 
    {
        move(3.0f, 0.0f);
    }
    if (IsKeyDown(KEY_W)) 
    {
        move(0.0f, -3.0f);
    }
    if (IsKeyDown(KEY_S)) 
    {
        move(0.0f, 3.0f);
    }

}

void Player::setName(const std::string & name) {
    _name = name;
}
void Player::setQuest(Quest& quest) {
    _current_quest = &quest;
}
void Player::setHp(int hp) {
    _hp = hp;
}

const std::string & Player::getName() const { return _name; }
const Quest * Player::getQuest()      const { return _current_quest; }
int Player::getHp()                   const { return _hp; }

void Player::interact() {

}