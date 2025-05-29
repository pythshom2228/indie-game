#include "tile.hpp"

Tile::Tile(const Rectangle & source_rec, const Rectangle& dest_rec)
: _source_rec(source_rec), _dest_rec(dest_rec) {

}

void Tile::render(const Texture2D tileset) const {
    DrawTexturePro(tileset, _source_rec, _dest_rec, {0.0f, 0.0f}, 0, WHITE);
}


