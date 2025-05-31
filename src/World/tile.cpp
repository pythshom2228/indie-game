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

    DrawRectangleLinesEx(
        {_hitbox.x + dest_rec.x, _hitbox.y + dest_rec.y, 
        _hitbox.width + dest_rec.width, _hitbox.height + dest_rec.height}, 
        3.0f, RED
    );
}

TileClass Tile::getTileClass() const { return _tile_class; }

void Tile::setTileClass(const TileClass &tile_class) {
    _tile_class = tile_class;
}

void Tile::setId(size_t id) {
    _id = id;
}
