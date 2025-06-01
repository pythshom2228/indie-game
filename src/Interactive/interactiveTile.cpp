#include "interactiveTile.hpp"

// InteractiveTile::InteractiveTile(const Vector2& position, float interactionRadius, const Tile& tile) 
//     : InteractiveObject(position, interactionRadius), _tile(tile) {}

// const Tile& InteractiveTile::getTile() const { return _tile; }
// void InteractiveTile::setTile(const Tile& newTile) { _tile = newTile; }

// void InteractiveTile::render(const Texture2D& tileset) const {
//     _tile.render(tileset, _position);  // Предполагаем, что Tile::render принимает позицию
// }

// void InteractiveTile::onInteract() override {
//     TraceLog(LOG_INFO, "Interacted with tile at (%.2f, %.2f)", _position.x, _position.y);
//     // Здесь можно добавить открытие сундука, активацию механизма и т. д.
// }