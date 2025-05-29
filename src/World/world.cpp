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
        return false;
    }

    // Получаем основную информацию о карте
    tinyxml2::XMLElement* map = doc.FirstChildElement("map");
    map->QueryAttribute("width", &_width);
    map->QueryAttribute("height", &_height);
    int tileWidth, tileHeight;
    map->QueryAttribute("tilewidth", &tileWidth);
    map->QueryAttribute("tileheight", &tileHeight);

    // Загружаем tileset
    tinyxml2::XMLElement* tileset = map->FirstChildElement("tileset");
    int firstgid;
    tileset->QueryAttribute("firstgid", &firstgid);
    
    std::string tilesetImagePath = tileset->FirstChildElement("image")->Attribute("source");
    _tileset = LoadTexture(tilesetImagePath.c_str());

    // Парсим слой с тайлами
    tinyxml2::XMLElement* layer = map->FirstChildElement("layer");
    tinyxml2::XMLElement* data = layer->FirstChildElement("data");
    
    // Поддерживаем только CSV формат данных
    if (strcmp(data->Attribute("encoding"), "csv") != 0) {
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
        int tileId = std::stoi(token) - firstgid; // Конвертируем в 0-based индекс
        
        if (tileId >= 0) {
            // Вычисляем позицию в tileset
            int tilesetCols = _tileset.width / tileWidth;
            int tilesetX = (tileId % tilesetCols) * tileWidth;
            int tilesetY = (tileId / tilesetCols) * tileHeight;

            Rectangle sourceRec = {
                static_cast<float>(tilesetX),
                static_cast<float>(tilesetY),
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
            _grid.push_back(tileId > 0 ? '1' : '0'); // '1' - есть тайл, '0' - пусто
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