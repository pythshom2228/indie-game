#include "tile.hpp"

Tile::Tile(const Rectangle & source_rec, const TileClass & tile_class)
: _source_rec(source_rec), _tile_class(tile_class) {

}

void Tile::render(const Texture2D & tileset, const Rectangle & dest_rec) const {
    DrawTextureRec(
        tileset,
        _source_rec, 
        {dest_rec.x, dest_rec.y},
        WHITE
    );
}