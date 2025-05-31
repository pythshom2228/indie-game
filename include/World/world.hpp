#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <sstream>

#include "player.hpp"
#include "tile.hpp"
#include "grid.hpp"


class World {
public:
    
    World();
    World(const Grid & filename, Player * player = nullptr);
    World(const std::string & filename, Player * player = nullptr);
    World(World&& world);
    
    World(const World & world) = delete;
    World& operator=(const World &) = delete;

    bool initWorld(const std::string & filename);

    void render() const;
    void update();

    void reset();
    
    void addEntity(const Entity & entity);
    void removeEntity(const std::string & entity_name);

    const Player * getPlayer() const;
    Grid getGrid() const;
    Texture2D getTileset() const;
    const std::string& getName() const;
    
    void setTileset(const Texture2D & tileset);
    void setPlayer(Player* player);
    void setFinished(bool _finished);
    
    bool isColidable(int x, int y) const;
    bool isFinished() const;
    
private:
    std::vector<std::unique_ptr<Entity>> _entities;
    Player* _player;

    Grid _grid;

    bool _is_finished;
    std::string _world_name;
};