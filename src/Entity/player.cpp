#include "player.hpp"

Player::Player() 
: Entity({}), _name("Renat"), _hp(3), _current_quest(nullptr) {
    
    _textures[RotationStates::Up] = LoadTexture(RES_PATH"player/WalkUpFirst.png");
    _textures[RotationStates::Right] = LoadTexture(RES_PATH"player/StandingRight.png");
    _textures[RotationStates::Down] = LoadTexture(RES_PATH"player/StandingDown.png");
    _textures[RotationStates::Left] = LoadTexture(RES_PATH"player/StandingLeft.png");
    

    initHitbox();

    scale(0.15f, 0.15f);
}

Player::Player(const std::array<Texture2D,DIRECTIONS_COUNT> _textures, const std::string & name,const Vector2 & position, int hp) 
: Entity(_textures, position), _name(name), _hp(hp), _current_quest(nullptr) {}

void Player::update() {

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