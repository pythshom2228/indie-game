#include <raylib.h>
#include <memory>

#include "entity.hpp"
#include "collidable.hpp"

class Tile : public Collidable {
public:

    Tile(const Rectangle & source_rec, const Rectangle& dest_rec);
    void render(const Texture2D tileset) const;

private:
    size_t _id;
    Rectangle _source_rec;
    Rectangle _dest_rec;
};