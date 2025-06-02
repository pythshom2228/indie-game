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

    _grid.render(Layer::Down);
    _player->render();
    _grid.render(Layer::Up);

    for (auto & interactive_object : _interactiv_objects) {
        interactive_object.render();
        DrawCircleV(interactive_object.getPosition(), 10.0f, RED);
        DrawCircleLinesV(interactive_object.getPosition(), interactive_object.getInteractiveRadius(), RED);
    }
    
    //DrawText(TextFormat("X: %f, Y: %f", (_player->getPosition().x / 256.0f), (_player->getPosition().y / 256.0f)), _player->getPosition().x, _player->getPosition().y, 20, WHITE);
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
    _player->setPosition(2.4f * 256.0f, 5.1f * 256.0f);

    InteractiveObject io({LoadTexture(RES_PATH"Interactive/purple_portal.png")});
    io.setPosition({13.5f * 256.0f, 5.5f * 256.0f});
    io.scale(0.2f, 0.2f);
    io.setIntaractiveRadius(130.0f);

    io.setInteract([this](){
        this->_is_finished = true;
    });

    _interactiv_objects.push_back(io);
    

}

bool Lobby::getgotoDogrld() const { return _gotoDogrld; }

void Dogrld::start() {

    initWorld("dog_world.tmx");
    _player->setPosition(4.5f * 256.0f, 33.5f * 256);

    InteractiveObject lever({});
    lever.setIntaractiveRadius(160.0f);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            this->_grid[14][3] = 17;
            this->_grid[14][2] = 15;
        }
    });
    lever.setPosition({2.5f * 256.0f, 14.5f * 256.0f});
    _interactiv_objects.push_back(lever);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            this->_grid[9][5] = 17;
            this->_grid[10][1] = 15;
        }
    });
    lever.setPosition({1.5f * 256.0f, 10.5f * 256.0f});
    _interactiv_objects.push_back(lever);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            this->_grid[9][10] = 17;
            this->_grid[2][2] = 15;
        }
    });
    lever.setPosition({2.5f * 256.0f, 2.5f * 256.0f});
    _interactiv_objects.push_back(lever);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            this->_grid[9][23] = 17; // Floor
            this->_grid[2][20] = 15; // Lever
        }
    });
    lever.setPosition({20.5f * 256.0f, 2.5f * 256.0f});
    _interactiv_objects.push_back(lever);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            this->_grid[4][24] = 17;
            this->_grid[16][21] = 15;
        }
    });
    lever.setPosition({21.5f * 256.0f, 16.5f * 256.0f});
    _interactiv_objects.push_back(lever);

//***********************************************//
lever.setInteract([this](){
    if (IsKeyPressed(KEY_E)) {
        this->_grid[21][3] = 17; // Floor
        this->_grid[17][16] = 15; // Lever
    }
});
lever.setPosition({16.5f * 256.0f, 17.5f * 256.0f});
_interactiv_objects.push_back(lever);
//***********************************************//
lever.setInteract([this](){
    if (IsKeyPressed(KEY_E)) {
        this->_grid[38][8] = 17; // Floor
        this->_grid[32][3] = 15; // Lever
    }
});
lever.setPosition({3.5f * 256.0f, 32.5f * 256.0f});
_interactiv_objects.push_back(lever);
//***********************************************//
lever.setInteract([this](){
    if (IsKeyPressed(KEY_E)) {
        this->_grid[38][10] = 17; // Floor
        this->_grid[29][16] = 15; // Lever
    }
});
lever.setPosition({16.5f * 256.0f, 29.5f * 256.0f});
_interactiv_objects.push_back(lever);
//***********************************************//
lever.setInteract([this](){
    if (IsKeyPressed(KEY_E)) {
        this->_grid[38][12] = 17; // Floor
        this->_grid[35][28] = 15; // Lever
    }
});
lever.setPosition({28.5f * 256.0f, 35.5f * 256.0f});
_interactiv_objects.push_back(lever);

//***********************************************//
    InteractiveObject portal({LoadTexture(RES_PATH"Interactive/purple_portal.png")});
    portal.scale(0.2f, 0.2f);
//***********************************************//
    portal.setInteract([this](){
        PlaySound(LoadSound(RES_PATH"UI/ButtonPressed.mp3"));
        this->_player->setPosition({8.0f * 256.0f, 16.5f * 256.0f});
    });
    portal.setPosition({26.5f * 256.0f, 4.5f * 256.0f});

    _interactiv_objects.push_back(portal);
//***********************************************//
    portal.setInteract([this](){
        PlaySound(LoadSound(RES_PATH"UI/ButtonPressed.mp3"));
        this->_player->setPosition({25.5f * 256.0f, 4.5f * 256.0f});
    });
    portal.setPosition({7.0f * 256.0f, 16.5f * 256.0f});

    _interactiv_objects.push_back(portal);
//***********************************************//
    portal.setInteract([this](){
        PlaySound(LoadSound(RES_PATH"UI/ButtonPressed.mp3"));
        this->_player->setPosition({17.5f * 256.0f, 22.5f * 256.0f});
    });
    portal.setPosition({3.0f * 256.0f, 24.5f * 256.0f});

    _interactiv_objects.push_back(portal);
//***********************************************//

    InteractiveObject red_portal({LoadTexture(RES_PATH"Interactive/portal_red.png")});

    red_portal.setInteract([this](){

    });
    red_portal.setPosition({18.0f * 256.0f, 37.5f * 256.0f});
    red_portal.scale(0.3f, 0.3f);

    _interactiv_objects.push_back(red_portal);
}