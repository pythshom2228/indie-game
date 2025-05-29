#include <World/world.hpp>
#include "world.hpp"
#include <tmxlite/Map.hpp>
#include <iostream>

World::World(const std::string & filename, Player * player)
: _filename(filename), _player(player) {
    loadFromFile(_filename);
    
}

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

    // for (const auto & entity : _entities) {
    //     entity->render();
    // }

    for (const auto & tile : _tiles) {
        tile.render(_tileset);
    }

    //DrawTexture(_tileset, 0, 0, WHITE);

}

void World::update() {

    // for (const auto & entity : _entities) {
    //     entity->update();
    // }

}

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

bool World::loadFromFile(const std::string& filename) {
    // Полный путь к файлу
    std::string fullPath = "resources/worlds/" + filename;
    
    // 1. Загрузка карты
    tmx::Map map;
    if (!map.load(fullPath)) {
        TraceLog(LOG_ERROR, "Failed to load map: %s", fullPath.c_str());
        return false;
    }
    
    // 2. Получение tileset'а (первого в списке)
    const auto& tilesets = map.getTilesets();
    if (tilesets.empty()) {
        TraceLog(LOG_ERROR, "No tilesets found in map");
        return false;
    }
    
    const auto& tileset = tilesets[0];
    std::string tilesetPath = tileset.getImagePath();
    
    // 3. Загрузка текстуры tileset'а
    _tileset = LoadTexture(tilesetPath.c_str());
    if (_tileset.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load tileset texture: %s", tilesetPath.c_str());
        return false;
    }
    
    TraceLog(LOG_INFO, "Successfully loaded tileset: %s", tilesetPath.c_str());
    
    
    const auto& layers = map.getLayers();
    for (const auto& layer : layers) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            
            // Сохраняем размеры карты
            _width = tileLayer.getSize().x;
            _height = tileLayer.getSize().y;
            
            // Заполняем сетку
            const auto& tiles = tileLayer.getTiles();
            _grid.reserve(tiles.size());
            
            for (const auto& tile : tiles) {
                _grid.push_back(tile.ID); // Сохраняем ID тайлов
            }
            
            TraceLog(LOG_INFO, "Loaded tile layer with %dx%d tiles", _width, _height);
            break; // Пока берем только первый слой
        }
    }

        // 5. Создание объектов Tile
        const auto& tilesetInfo = map.getTilesets()[0];
        unsigned int tileWidth = tilesetInfo.getTileSize().x;
        unsigned int tileHeight = tilesetInfo.getTileSize().y;
        
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                int index = y * _width + x;
                unsigned int tileID = _grid[index];
                
                if (tileID == 0) continue; // 0 - пустой тайл
                
                // Позиция на карте
                Rectangle destRec = {
                    x * tileWidth * 1.0f,
                    y * tileHeight * 1.0f,
                    tileWidth * 1.0f,
                    tileHeight * 1.0f
                };
                
                // Позиция в tileset'е
                unsigned int tilesetColumns = tilesetInfo.getColumnCount();
                unsigned int tilesetX = (tileID - 1) % tilesetColumns;
                unsigned int tilesetY = (tileID - 1) / tilesetColumns;
                
                Rectangle sourceRec = {
                    tilesetX * tileWidth * 1.0f,
                    tilesetY * tileHeight * 1.0f,
                    tileWidth * 1.0f,
                    tileHeight * 1.0f
                };
                
                _tiles.emplace_back(sourceRec, destRec);
            }
        }
        
        TraceLog(LOG_INFO, "Created %d tile objects", _tiles.size());


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

const Player * World::getPlayer() const { return _player;   }
std::string World::getFilename()  const { return _filename; }
Texture2D World::getTileset()     const { return _tileset;  }

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