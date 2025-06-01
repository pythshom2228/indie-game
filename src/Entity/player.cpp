#include "player.hpp"
static bool isWASDDownKeysdown();
#include <iostream>

Player::Player() 
: Entity({}), _name("Renat"), _hp(3), _current_quest(nullptr) {
    _velocity = 2.5;

    scale(0.15f, 0.15f);

    _textures[RotationStates::Up] = LoadTexture(RES_PATH"player/WalkUpFirst.png");
    _textures[RotationStates::Right] = LoadTexture(RES_PATH"player/StandingRight.png");
    _textures[RotationStates::Down] = LoadTexture(RES_PATH"player/StandingDown.png");
    _textures[RotationStates::Left] = LoadTexture(RES_PATH"player/StandingLeft.png");

    Texture2D walking_right_animation = LoadTexture(RES_PATH"player/Animations/WalkingRight.png");
    Texture2D walking_left_animation = LoadTexture(RES_PATH"player/Animations/WalkingLeft.png");
    Texture2D walking_up_animation = LoadTexture(RES_PATH"player/Animations/WalkingUp.png");
    Texture2D walking_down_animation = LoadTexture(RES_PATH"player/Animations/WalkingDown.png");

    
    _animation_component.setAnimation(
        "WalkingRight",
        walking_right_animation,
        _scale,
        walking_right_animation.width / 2,
        walking_right_animation.height,
        2,
        1 / _velocity
    );
    _animation_component.setAnimation(
        "WalkingLeft",
        walking_left_animation,
        _scale,
        walking_left_animation.width / 2,
        walking_left_animation.height,
        2,
        1 / _velocity
    );
    _animation_component.setAnimation(
        "WalkingUp",
        walking_up_animation,
        _scale,
        walking_up_animation.width / 2,
        walking_up_animation.height,
        2,
        1 / _velocity
    );
    _animation_component.setAnimation(
        "WalkingDown",
        walking_down_animation,
        _scale,
        walking_down_animation.width / 2,
        walking_down_animation.height,
        2,
        1 / _velocity
    );
    // e.t.c.

    initHitbox();

}

Player::Player(const std::array<Texture2D,DIRECTIONS_COUNT> _textures, const std::string & name,const Vector2 & position, int hp) 
: Entity(_textures, position), _name(name), _hp(hp), _current_quest(nullptr) {}

void Player::update() {
    updateAnimation();
}

static bool isWASDDownKeysdown() {
    if (IsKeyDown(KEY_A))
        return true;
    else if (IsKeyDown(KEY_W))
        return true;
    else if (IsKeyDown(KEY_S))
        return true;
    else if (IsKeyDown(KEY_D))
        return true;
    
    return false;
}

void Player::render() const {
    
    const Texture2D& texture = _textures[_rotation_state];

    Vector2 origin = {
        (texture.width * _scale.x) / 2,    // Центр по X
        (texture.height * _scale.y) / 2    // Центр по Y
    };
    
    if(isWASDDownKeysdown()) {
        switch (_rotation_state) {
            case RotationStates::Down:
                _animation_component.draw(_position);
                break;
            
            case RotationStates::Up:
                _animation_component.draw(_position);    
                break;

            case RotationStates::Right:
                _animation_component.draw(_position);
                break;
            
                case RotationStates::Left:
                _animation_component.draw(_position);
                break;
            default:
                break;
        }
    }
    else {
        
        Rectangle source_rect = {
            0.0f, 0.0f,                       // Начало текстуры (x, y)
            (float)texture.width,              // Ширина исходной текстуры
            (float)texture.height              // Высота исходной текстуры
        };
        
        Rectangle dest_rect = {
            _position.x,                       // Центр по X
            _position.y,                       // Центр по Y
            texture.width * _scale.x,          // Ширина с масштабом
            texture.height * _scale.y          // Высота с масштабом
        };
        

        
        // Рисуем текстуру с центром в _position
        
        DrawTexturePro(
            texture,
            source_rect,
            dest_rect,
            origin,
            0.0f,                              // Угол поворота (если нужно)
            WHITE                              // Цвет (можно добавить поле)
        );
    }
        
    

    DrawRectangleLinesEx(
        {_hitbox.x, _hitbox.y, 
        _hitbox.width, _hitbox.height}, 
        3.0f, RED
    );

    DrawRectangleLinesEx(
        {_up_hitbox.x, _up_hitbox.y, 
            _up_hitbox.width, _up_hitbox.height}, 
            3.0f, GREEN
    );

    DrawRectangleLinesEx(
        {_down_hitbox.x, _down_hitbox.y, 
            _down_hitbox.width, _down_hitbox.height}, 
            3.0f, BLUE
    );
    
    // Отладочная точка в центре (можно убрать)
    DrawCircle(_position.x, _position.y, 2.0f, BLUE);


    int x1 = _hitbox.x;
    int y1 = _hitbox.y;

    int x2 = (_hitbox.x + _hitbox.width);
    int y2 = _hitbox.y;

    int x3 = (_hitbox.x + _hitbox.width);
    int y3 = (_hitbox.y + _hitbox.height);

    int x4 = _hitbox.x;
    int y4 = (_hitbox.y + _hitbox.height);

    DrawCircle(x1, y1, 15.0f, GREEN);
    DrawCircle(x2, y2, 15.0f, RED);
    DrawCircle(x3, y3, 15.0f, BLUE);
    DrawCircle(x4, y4, 15.0f, YELLOW);

    int x = _position.x / 256.0f;
    int y = _position.y / 256.0f;

    std::string coord = std::to_string(x) + " " + std::to_string(y);

    DrawText(coord.c_str(), _position.x - 30, _position.y - 170, 50, RED);
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
float Player::getVelocity() {
    return _velocity;
}