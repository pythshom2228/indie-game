#include <raylib.h>
#include <memory>

#include "entity.hpp"
#include "collidable.hpp"

enum TileClass {
    Floor = 0,
    Wall = 1
};

class Tile : public Collidable {
public:

    Tile(const Rectangle & source_rec, const TileClass & _tile_class);
    void render(const Texture2D & tileset, const Rectangle & dest_rec) const;

    size_t _id;
    TileClass _tile_class;
    Rectangle _source_rec;
};