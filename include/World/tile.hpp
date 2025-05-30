#include <raylib.h>
#include <memory>

#include "entity.hpp"
#include "collidable.hpp"

class Tile : public Collidable {
public:

    Tile(const Rectangle & source_rec);
    void render(const Texture2D & tileset, const Rectangle & dest_rec) const;

    size_t _id;
    Rectangle _source_rec;
};