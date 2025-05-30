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
    const int tileWidth = 256;
    const int tileHeight = 256;

    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {

            int tileIndex = _grid[y * _width + x];

            if (tileIndex >= 0 && tileIndex < static_cast<int>(_tiles.size())) {
                Rectangle destRec = {
                    static_cast<float>(x * tileWidth),
                    static_cast<float>(y * tileHeight),
                    static_cast<float>(tileWidth),
                    static_cast<float>(tileHeight)
                };
                
                _tiles[tileIndex].render(_tileset, destRec);
            }
        }
    }

    _player->render();
}

void World::update() {

    
    _player->update();


}

bool World::loadFromFile(const std::string & filename) {
    tmx::Map map;
    
    if (!map.load(RES_PATH"worlds/" + filename)) {
        return false;
    }

    const auto& mapSize = map.getTileCount();
    _width = mapSize.x;
    _height = mapSize.y;

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

    // Очищаем и готовим структуры данных
    _tiles.clear();
    _grid.clear();
    _grid.resize(_width * _height, -1); // -1 означает отсутствие тайла

    // Словарь для хранения уже добавленных тайлов (ID -> индекс в _tiles)
    std::unordered_map<unsigned int, unsigned int> tileIdToIndex;

    const auto& layers = map.getLayers();
    for (const auto& layer : layers) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto& tiles = tileLayer.getTiles();
            
            for (unsigned int y = 0; y < mapSize.y; ++y) {
                for (unsigned int x = 0; x < mapSize.x; ++x) {
                    const auto& tile = tiles[y * mapSize.x + x];
                    if (tile.ID == 0) continue;

                    // Если тайл с таким ID еще не добавлен в _tiles
                    if (tileIdToIndex.find(tile.ID) == tileIdToIndex.end()) {
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
                        
                        // Добавляем тайл в вектор и запоминаем его индекс
                        tileIdToIndex[tile.ID] = _tiles.size();
                        _tiles.emplace_back(sourceRec);
                        _tiles.back()._id = tile.ID; // Сохраняем оригинальный ID
                    }

                    // Записываем индекс тайла в grid
                    _grid[y * _width + x] = tileIdToIndex[tile.ID];
                }
            }
        }
    }

    // Вывод grid для отладки
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            std::cout << _grid[i * _width + j] << " ";
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

int World::getTileId(int x, int y) const {
    return _grid.at(y * _width + x);
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