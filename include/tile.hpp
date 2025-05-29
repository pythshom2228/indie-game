#include <raylib.h>
#include <memory>
#include "Entities/entity.hpp"

class Tile  {
public:

    Tile(const std::shared_ptr<Texture2D>& texture, const Rectangle& source);
    bool checkCollission(const Entity& object);
    void render();

private:
    size_t _id;
    Rectangle source_rect;
    std::shared_ptr<Texture2D> texture;
};