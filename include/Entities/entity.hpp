#include <raylib.h>
#include <vector>
#include <string>
#include <Animation/animation_component.hpp>

class Entity {
public:

    Entity() {}

    virtual bool checkCollission(const Entity& first, const Entity& second);
    virtual void render() = 0;

    virtual ~Entity() {};

private:

    Rectangle _hitbox;
    std::vector<Texture2D> _textures;
    Vector2 _position;
    int _velocity;
    bool _isColliadable;
    int _id;
    AnimationComponent _component;
};