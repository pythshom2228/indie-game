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

    for (auto & npc : _npcs) {
        npc.render();
    }

    _player->render();

    _grid.render(Layer::Up);
    
    for (auto & interactive_object : _interactiv_objects) {
        interactive_object.render();
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

    for (auto & npc : _npcs) {
        if (npc.isPointInRange(_player->getPosition())) {
            npc.onInteract();
        } else {
            npc.setHasPlayedSound(false);
            npc.update();
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

void World::addNPC(const NPC &nps) {
    _npcs.push_back(nps);
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

    InteractiveObject io({LoadTexture(RES_PATH"Interactive/purple_portal.png")}, 130.0f);
    io.setPosition({13.5f * 256.0f, 5.5f * 256.0f});
    io.scale(0.2f, 0.2f);

    io.setInteract([this](){
        this->_is_finished = true;
    });

    _interactiv_objects.push_back(io);
    

    NPC bob({LoadTexture(RES_PATH"Interactive/bob.png")}, {5.0f * 256.0f, 2.9f * 256.0f});
    bob.setIntaractiveRadius(230.0f);
    bob.scale(0.15f, 0.15f);
    // В коде инициализации NPC
    bob.setInteract([this]() {  // Захватываем bob по ссылке, чтобы менять его поле
        Vector2 bobPos = {5.0f * 256.0f, 2.9f * 256.0f};
        float textSize = 50;
        float padding = 20.0f;
        const char* text = "TELEPORTATOR THREE THOUSAND!!";

        Vector2 textSizeMeasured = MeasureTextEx(GetFontDefault(), text, textSize, 10.0f);

        Rectangle textBox = {
            bobPos.x - textSizeMeasured.x/2 - padding,
            bobPos.y - 250.0f,
            textSizeMeasured.x + 2*padding,
            textSizeMeasured.y + 2*padding
        };

        DrawRectangleRounded(textBox, 0.3f, 8, LIGHTGRAY);
        DrawRectangleRoundedLines(textBox, 0.3f, 8, DARKGRAY);

        DrawText(text, 
                 textBox.x + padding, 
                 textBox.y + padding, 
                 textSize, DARKBLUE);
        
        Vector2 tail[3] = {
            {bobPos.x, textBox.y + textBox.height},
            {bobPos.x - 15.0f, textBox.y + textBox.height + 15.0f},
            {bobPos.x + 15.0f, textBox.y + textBox.height + 15.0f}
        };
        DrawTriangle(tail[0], tail[1], tail[2], LIGHTGRAY);
        DrawTriangleLines(tail[0], tail[1], tail[2], DARKGRAY);

        // Если звук ещё не играл — проигрываем и ставим флаг
        if (!this->_npcs[0].hasPlayedSound()) {
            int rand = GetRandomValue(0, 5);

            switch (rand)
            {
            case 0:
                PlaySound(LoadSound(RES_PATH"UI/crazydavelong0.mp3"));
                break;
            case 1:
                PlaySound(LoadSound(RES_PATH"UI/crazydavelong1.mp3"));
                break;
            case 2:
                PlaySound(LoadSound(RES_PATH"UI/crazydavelong2.mp3"));
                break;
            case 3:
                PlaySound(LoadSound(RES_PATH"UI/crazydavelong3.mp3"));
                break;
            case 4:
                PlaySound(LoadSound(RES_PATH"UI/crazydavelong4.mp3"));
                break;
            case 5:
                PlaySound(LoadSound(RES_PATH"UI/crazydavelong5.mp3"));
                break;
            }

            this->_npcs[0].setHasPlayedSound(true);
        }
    });

    _npcs.push_back(bob);


}

void Dogrld::start() {
    PlaySound(LoadSound(RES_PATH"UI/dog_world_sound.mp3"));
    initWorld("dog_world.tmx");
    _player->setPosition(2.5f * 256.0f, 17.5f * 256);

    InteractiveObject lever({});
    lever.setIntaractiveRadius(160.0f);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
            this->_grid[14][3] = 17;
            this->_grid[14][2] = 15;
        }
    });
    lever.setPosition({2.5f * 256.0f, 14.5f * 256.0f});
    _interactiv_objects.push_back(lever);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
            this->_grid[9][5] = 17;
            this->_grid[10][1] = 15;
        }
    });
    lever.setPosition({1.5f * 256.0f, 10.5f * 256.0f});
    _interactiv_objects.push_back(lever);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
            this->_grid[9][10] = 17;
            this->_grid[2][2] = 15;
        }
    });
    lever.setPosition({2.5f * 256.0f, 2.5f * 256.0f});
    _interactiv_objects.push_back(lever);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
            this->_grid[9][23] = 17; // Floor
            this->_grid[2][20] = 15; // Lever
        }
    });
    lever.setPosition({20.5f * 256.0f, 2.5f * 256.0f});
    _interactiv_objects.push_back(lever);
//***********************************************//
    lever.setInteract([this](){
        if (IsKeyPressed(KEY_E)) {
            PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
            this->_grid[4][24] = 17;
            this->_grid[16][21] = 15;
        }
    });
    lever.setPosition({21.5f * 256.0f, 16.5f * 256.0f});
    _interactiv_objects.push_back(lever);

//***********************************************//
lever.setInteract([this](){
    if (IsKeyPressed(KEY_E)) {
        PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
        this->_grid[21][3] = 17; // Floor
        this->_grid[17][16] = 15; // Lever
    }
});
lever.setPosition({16.5f * 256.0f, 17.5f * 256.0f});
_interactiv_objects.push_back(lever);
//***********************************************//
lever.setInteract([this](){
    if (IsKeyPressed(KEY_E)) {
        PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
        this->_grid[38][8] = 17; // Floor
        this->_grid[32][3] = 15; // Lever
    }
});
lever.setPosition({3.5f * 256.0f, 32.5f * 256.0f});
_interactiv_objects.push_back(lever);
//***********************************************//
lever.setInteract([this](){
    if (IsKeyPressed(KEY_E)) {
        PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
        this->_grid[38][10] = 17; // Floor
        this->_grid[29][16] = 15; // Lever
    }
});
lever.setPosition({16.5f * 256.0f, 29.5f * 256.0f});
_interactiv_objects.push_back(lever);
//***********************************************//
lever.setInteract([this](){
    if (IsKeyPressed(KEY_E)) {
        PlaySound(LoadSound(RES_PATH"UI/door.mp3"));
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