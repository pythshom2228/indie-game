#include "tile.hpp"

Tile::Tile(const Rectangle & source_rec, const Rectangle& dest_rec)
: _source_rec(source_rec), _dest_rec(dest_rec) {

}

void Tile::render(const Texture2D tileset) const {
    DrawTextureRec(tileset, _source_rec, {_dest_rec.x, _dest_rec.y}, WHITE);
}


