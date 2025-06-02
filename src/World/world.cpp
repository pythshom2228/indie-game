#include "world.hpp"

#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>

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

    _grid.render(Layer::Down);
    _player->render();
    _grid.render(Layer::Up);

    for (auto & interactive_object : _interactiv_objects) {
        interactive_object.render();
        DrawCircleV(interactive_object.getPosition(), 10.0f, RED);
        DrawCircleLinesV(interactive_object.getPosition(), interactive_object.getInteractiveRadius(), RED);
    }
    
    DrawText(TextFormat("X: %f, Y: %f", (_player->getPosition().x / 256.0f), (_player->getPosition().y / 256.0f)), _player->getPosition().x, _player->getPosition().y, 20, WHITE);
}

void World::update() {
    
    _player->update();

    for (auto & interactive_object : _interactiv_objects) {
        if (interactive_object.isPointInRange(_player->getPosition())) {
            interactive_object.onInteract();
        }
    }

}

void World::reset() {

}

void World::addEntity(const Entity & entity) {

}

void World::addInteractiveObject(const InteractiveObject &interactive_object) {
    _interactiv_objects.push_back(interactive_object);
}

void World::removeEntity(const std::string & entity_name) {

}

void World::removeInteractiveObject(const std::string &entity_name) {

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

void Lobby::start() {
    
    initWorld("lobby.tmx");
    _player->setPosition(2.4f * 256.0f, 5.1f * 256);

    InteractiveObject io({LoadTexture(RES_PATH"Interactive/purple_portal.png")});
    io.setPosition({13.5f * 256.0f, 5.5f * 256.0f});
    io.scale(0.2f, 0.2f);

    _interactiv_objects.push_back(io);
    

}

void Dogrld::start() {
    
    initWorld("dog_world.tmx");
    _player->setPosition(3.0f * 256.0f, 17.0f * 256);

    InteractiveObject io({LoadTexture(RES_PATH"Interactive/purple_portal.png")});
    io.setPosition({13.5f * 256.0f, 5.5f * 256.0f});
    io.scale(0.2f, 0.2f);

    _interactiv_objects.push_back(io);
    

}