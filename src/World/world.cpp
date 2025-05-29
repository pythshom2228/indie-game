#include <World/world.hpp>
#include "world.hpp"
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

    // for (const auto & tile : _tiles) {
    //     tile.render(_tileset);
    // }

}

void World::update() {

    // for (const auto & entity : _entities) {
    //     entity->update();
    // }

}

bool World::loadFromFile(const std::string& filename) {
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