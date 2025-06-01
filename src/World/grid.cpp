#include <iostream>

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Map.hpp>

#include "grid.hpp"

Grid::Grid(const std::vector<int> &grid, const std::vector<Tile> &tiles, const Texture2D &tileset, int width, int height)
: _grid(grid), _tiles(tiles), _tileset(tileset), _width(width), _height(height) {}

Grid::Grid(const std::string &filename) {
    loadFromFile(filename);
}

bool Grid::checkCollision(const Rectangle & hitbox) {

    int x1 = hitbox.x / 256.0f;
    int y1 = hitbox.y / 256.0f;

    int x2 = (hitbox.x + hitbox.width) / 256.0f;
    int y2 = hitbox.y / 256.0f;

    int x3 = (hitbox.x + hitbox.width) / 256.0f;
    int y3 = (hitbox.y + hitbox.height) / 256.0f;

    int x4 = hitbox.x / 256.0f;
    int y4 = (hitbox.y + hitbox.height) / 256.0f;

    if 
    (
        _tiles[(*this)[y1][x1]].getTileClass() == TileClass::Wall ||
        _tiles[(*this)[y2][x2]].getTileClass() == TileClass::Wall ||
        _tiles[(*this)[y3][x3]].getTileClass() == TileClass::Wall ||
        _tiles[(*this)[y4][x4]].getTileClass() == TileClass::Wall
    ) 
    {
        return true;
    }
    return false;
}

void Grid::render() const {
    const int tileWidth = 256;
    const int tileHeight = 256;
    
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {

            int tileIndex = _grid[y * _width + x];

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

Texture2D Grid::getTileset() const { return _tileset; }
int Grid::getWidth()  const { return _width; }
int Grid::getHeight() const { return _height; }

void Grid::setTileset(const Texture2D & tileset) {
    _tileset = tileset;
}

void Grid::setWidth(int width) {
    _width = width;
}

void Grid::setHeight(int height) {
    _height = height;
}


Grid::Proxy Grid::operator[](int row)
{
    if (row < 0 || row >= _height) {
        throw std::out_of_range("Row index out of range");
    }
    return Proxy(_grid, row, _width);
}

const Grid::Proxy Grid::operator[](int row) const {
    if (row < 0 || row >= _height) {
        throw std::out_of_range("Row index out of range");
    }
    return Proxy(_grid, row, _width);
}

Grid::Proxy::Proxy(std::vector<int>& grid, int row, int width) : _grid(&grid), _row(row), _width(width) {}

Grid::Proxy::Proxy(const std::vector<int>& grid, int row, int width) : _constGrid(&grid), _row(row), _width(width) {}

int& Grid::Proxy::operator[](int col) {
    return (*_grid)[_row * _width + col];
}

const int& Grid::Proxy::operator[](int col) const {
    return (*_constGrid)[_row * _width + col];
}

bool Grid::loadFromFile(const std::string & filename) {
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
            
            TileClass tile_class;
            
            if (tileLayer.getName() == "Floor") tile_class = TileClass::Floor;
            else tile_class = TileClass::Wall;

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
                        _tiles.emplace_back(sourceRec, tile_class);
                        _tiles.back().setId(tile.ID); // Сохраняем оригинальный ID
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