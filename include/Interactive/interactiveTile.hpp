#pragma once

#include "interactiveObject.hpp"
#include "tile.hpp"

class InteractiveTile : public InteractiveObject {
public:
    InteractiveTile(const Vector2& position, float interactionRadius, const Tile& tile);

    // Получение и изменение тайла
    const Tile& getTile() const;
    void setTile(const Tile& newTile);

    // Отрисовка тайла
    void render(const Texture2D& tileset) const;

    // Переопределяем взаимодействие
    void onInteract() override;

private:
    Tile _tile;  // Тайл, связанный с этим объектом
};