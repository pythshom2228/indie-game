#include <raylib.h>
#include <vector>
#include <string>
#include <Animation/animation_component.hpp>
#include "../collidable.hpp"

class Entity : public Collidable{
public:

    Entity() {}

    bool checkCollission(const Collidable& obj);
    void move(const Vector2& dest);
    void move(float x, float y);
    
    void setPosition(const Vector2& position);
    void setPosition(float x, float y);

    const Vector2& getPosition();
    

    virtual void update() = 0;
    virtual void render() = 0;

    virtual ~Entity() {};

protected:

    Rectangle _hitbox;
    std::vector<Texture2D> _textures;
    Vector2 _position;
    int _velocity;
    bool _isColliadable;
    int _id;
    AnimationComponent _component;
};