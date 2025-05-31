#include "world.hpp"

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <iostream>

World::World()
: _player(nullptr) {}

World::World(const Grid & grid, Player * player)
: _grid(std::move(grid)), _player(player) {}

World::World(const std::string &filename, Player* player) 
: World(Grid(filename)) {
    _player = player;    
}

World::World(World&& world)
: 
_grid(std::move(world._grid)), 
_entities(std::move(world._entities)),
_player(world._player),
_is_finished(world._is_finished) 
{
    world._player = nullptr;
}

bool World::initWorld(const std::string &filename) {
    return _grid.loadFromFile(filename);
}

void World::render() const
{

    _grid.render(0);
    _player->render();
    _grid.render(1);
}

void World::update() {
    
    _player->update();
}

void World::reset() {

}

void World::addEntity(const Entity & entity) {

}

void World::removeEntity(const std::string & entity_name) {

}

const Player * World::getPlayer()   const { return _player;   }
Grid World::getGrid()               const { return _grid; }
const std::string &World::getName() const { return _world_name; }

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