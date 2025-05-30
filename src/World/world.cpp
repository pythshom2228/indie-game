#include "world.hpp"

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <iostream>

World::World()
: _player(nullptr) {}

World::World(const std::string & filename, Player * player)
: _filename(filename), _player(player) {}

World::World(World&& world)
: _width(world._width), _height(world._height), 
_filename(std::move(world._filename)), 
_entities(std::move(world._entities)),
_tiles(std::move(world._tiles)),
_grid(std::move(world._grid)),
_player(world._player),
_is_finished(world._is_finished) {
    world._player = nullptr;
}

void World::render() const {
    for (const auto& tile : _tiles) {
        tile.render(_tileset);
    }

    // for (const auto& entity : _entities) {
    //     entity->render();
    // }

    _player->render();
}

void World::update() {

    if (IsKeyDown(KEY_A)) 
    {
        _player->move(-3.0f, 0.0f);

    }
    if (IsKeyDown(KEY_D)) 
    {
        _player->move(3.0f, 0.0f);
    }
    if (IsKeyDown(KEY_W)) 
    {
        _player->move(0.0f, -3.0f);
    }
    if (IsKeyDown(KEY_S)) 
    {
        _player->move(0.0f, 3.0f);
    }

    

}


bool World::loadFromFile(const std::string & filename) {
    tmx::Map map;
    
    if (!map.load(RES_PATH"worlds/" + filename)) {
        return false;
    }

    const auto& mapSize = map.getTileCount();
    _width = mapSize.x;
    _height = mapSize.y;

    // Явно задаем размер тайла из TMX (256x256)
    const int tileWidth = 256;
    const int tileHeight = 256;

    const auto& tilesets = map.getTilesets();
    if (tilesets.empty()) {
        return false;
    }

    const auto& tileset = tilesets[0];
    std::string tilesetPath = tileset.getImagePath();
    
    _tileset = LoadTexture(tilesetPath.c_str());
    if (_tileset.id == 0) {
        return false;
    }

    _tiles.clear();
    _grid.clear();
    _grid.resize(_width * _height, 0); // Инициализируем нулями

    const auto& layers = map.getLayers();
    for (const auto& layer : layers) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto& tiles = tileLayer.getTiles();
            
            for (unsigned int y = 0; y < mapSize.y; ++y) {
                for (unsigned int x = 0; x < mapSize.x; ++x) {
                    const auto& tile = tiles[y * mapSize.x + x];

                    Rectangle destRec = {
                        static_cast<float>(x * tileWidth),
                        static_cast<float>(y * tileHeight),
                        static_cast<float>(tileWidth),
                        static_cast<float>(tileHeight)
                    };

                    const unsigned int tilesetColumns = tileset.getColumnCount();
                    const unsigned int relativeID = tile.ID - tileset.getFirstGID();
                    
                    int tilesetX = (relativeID % tilesetColumns) * tileWidth;
                    int tilesetY = (relativeID / tilesetColumns) * tileHeight;
                        
                    Rectangle sourceRec = {
                        static_cast<float>(tilesetX),
                        static_cast<float>(tilesetY),
                        static_cast<float>(tileWidth),
                        static_cast<float>(tileHeight)
                    };

                    _tiles.emplace_back(sourceRec, destRec);
                    _grid[y * _width + x] = tile.ID; // Сохраняем оригинальный ID тайла
                }
            }
        }
    }

    // Отладочный вывод (исправлена ошибка в индексации)
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            std::cout << _grid[i * _width + j] << " "; // Исправлено с _height на _width
        }
        std::cout << std::endl;
    }

    return true;
}

bool World::saveToFile(const std::string & filename) {

}

void World::reset() {

}

void World::addEntity(const Entity & entity) {

}

void World::removeEntity(const std::string & entity_name) {

}

std::unique_ptr<Entity>& World::operator[](int idx) {

}

const std::unique_ptr<Entity>& World::operator[](int idx) const {

}

Tile World::getTile(int x, int y) const {

}

const Player * World::getPlayer()   const { return _player;   }
std::string World::getFilename()    const { return _filename; }
const std::string& World::getName() const { return _world_name; }
Texture2D World::getTileset()       const { return _tileset;  }

void World::setTileset(const Texture2D & tileset) {
    _tileset = tileset;
}

void World::setPlayer(Player* player) {
    _player = player;
}

void World::setFinished(bool finished) {
    _is_finished = finished;
}

bool World::isColidable(int x, int y) const {

}
bool World::isFinished() const {
    return _is_finished;
}