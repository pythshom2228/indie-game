#include <World/world.hpp>
#include "world.hpp"

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

}

void World::update() {

    // for (const auto & entity : _entities) {
    //     entity->update();
    // }

}

bool World::loadFromFile(const std::string& filename) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS) {
        TraceLog(LOG_ERROR, "Failed to load TMX file: %s", filename.c_str());
        return false;
    }

    // Получаем основную информацию о карте
    tinyxml2::XMLElement* map = doc.FirstChildElement("map");
    if (!map) {
        TraceLog(LOG_ERROR, "No 'map' element in TMX file");
        return false;
    }

    map->QueryAttribute("width", &_width);
    map->QueryAttribute("height", &_height);
    
    int tileWidth = 0, tileHeight = 0;
    map->QueryAttribute("tilewidth", &tileWidth);
    map->QueryAttribute("tileheight", &tileHeight);

    // Проверка корректности размеров тайлов
    if (tileWidth <= 0 || tileHeight <= 0) {
        TraceLog(LOG_ERROR, "Invalid tile size: %dx%d", tileWidth, tileHeight);
        return false;
    }

    // Загружаем tileset
    tinyxml2::XMLElement* tileset = map->FirstChildElement("tileset");
    if (!tileset) {
        TraceLog(LOG_ERROR, "No 'tileset' element in TMX file");
        return false;
    }

    int firstgid = 1; // Значение по умолчанию
    tileset->QueryAttribute("firstgid", &firstgid);
    
    tinyxml2::XMLElement* image = tileset->FirstChildElement("image");
    if (!image) {
        TraceLog(LOG_ERROR, "No 'image' element in tileset");
        return false;
    }

    const char* tilesetPath = image->Attribute("source");
    if (!tilesetPath) {
        TraceLog(LOG_ERROR, "No 'source' attribute in tileset image");
        return false;
    }

    _tileset = LoadTexture(tilesetPath);
    if (_tileset.width == 0 || _tileset.height == 0) {
        TraceLog(LOG_ERROR, "Failed to load tileset: %s", tilesetPath);
        return false;
    }

    // Проверка делителя перед делением
    if (tileWidth == 0) {
        TraceLog(LOG_ERROR, "Tile width cannot be zero");
        UnloadTexture(_tileset);
        return false;
    }

    int tilesetCols = _tileset.width / tileWidth;
    int tilesetRows = _tileset.height / tileHeight;

    // Парсим слой с тайлами
    tinyxml2::XMLElement* layer = map->FirstChildElement("layer");
    if (!layer) {
        TraceLog(LOG_ERROR, "No 'layer' element in TMX file");
        UnloadTexture(_tileset);
        return false;
    }

    tinyxml2::XMLElement* data = layer->FirstChildElement("data");
    if (!data) {
        TraceLog(LOG_ERROR, "No 'data' element in layer");
        UnloadTexture(_tileset);
        return false;
    }

    // Поддерживаем только CSV формат данных
    if (strcmp(data->Attribute("encoding"), "csv") != 0) {
        TraceLog(LOG_ERROR, "Only CSV-encoded maps are supported");
        UnloadTexture(_tileset);
        return false;
    }

    std::string csvData = data->GetText();
    std::istringstream iss(csvData);
    std::string token;
    _grid.clear();
    _tiles.clear();

    int x = 0, y = 0;
    while (std::getline(iss, token, ',')) {
        // Пропускаем пустые токены
        if (token.empty()) continue;

        int tileId = std::stoi(token) - firstgid;
        
        if (tileId >= 0) {
            // Безопасное вычисление позиции в tileset
            int tileX = (tileId % tilesetCols);
            int tileY = (tileId / tilesetCols);

            // Проверка выхода за границы tileset
            if (tileX >= tilesetCols || tileY >= tilesetRows) {
                TraceLog(LOG_WARNING, "Tile ID %d out of bounds in tileset", tileId + firstgid);
                continue;
            }

            Rectangle sourceRec = {
                static_cast<float>(tileX * tileWidth),
                static_cast<float>(tileY * tileHeight),
                static_cast<float>(tileWidth),
                static_cast<float>(tileHeight)
            };

            Rectangle destRec = {
                static_cast<float>(x * tileWidth),
                static_cast<float>(y * tileHeight),
                static_cast<float>(tileWidth),
                static_cast<float>(tileHeight)
            };

            _tiles.emplace_back(sourceRec, destRec);
            _grid.push_back('1');
        } else {
            _grid.push_back('0');
        }

        x++;
        if (x >= _width) {
            x = 0;
            y++;
        }
    }

    _filename = filename;
    TraceLog(LOG_INFO, "Successfully loaded map: %s (%dx%d tiles)", 
             filename.c_str(), _width, _height);
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