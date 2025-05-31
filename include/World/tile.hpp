#pragma once

#include <raylib.h>
#include <memory>

#include "entity.hpp"
#include "collidable.hpp"

enum class TileClass {
    Floor = 0,
    Wall = 1
};

class Tile : public Collidable {
public:

    Tile(const Rectangle & source_rec, const TileClass & _tile_class);
 
    void render(const Texture2D & tileset, const Rectangle & dest_rec) const;

    TileClass getTileClass() const;

    void setTileClass(const TileClass & tile_class);
    void setId(size_t id);

private:
    size_t _id;
    TileClass _tile_class;
    Rectangle _source_rec;
};