#pragma once

#include <vector>
#include <map>

#include <string>
#include <memory>

#include "player.hpp"
#include "tile.hpp"


class World {
public:
    World(const std::string & filename);
    World(World&& world);
    
    World(const World & world) = delete;
    World& operator=(const World &) = delete;
    
    void render() const;
    void update();
    
    bool loadFromFile(const std::string & filename);
    bool saveToFile(const std::string & filename);

    void reset();
    
    void addEntity(const Entity & entity);
    void removeEntity(const std::string & entity_name);
    
    std::unique_ptr<Entity>& operator[](int idx);
    const std::unique_ptr<Entity>& operator[](int idx) const;
    
    Tile getTile(int x, int y) const;
    const Player * getPlayer() const;
    std::string getFilename() const;
    
    void setTile()
    void setPlayer(Player* player);
    void setFinished(bool _finished);
    
    bool isColidable(int x, int y) const;
    bool isFinished() const;
    
private:
    Player* _player;
    std::map<int, std::unique_ptr<Entity>_entities;
    std::vector<Tile> _tiles;

    std::vector<char> _grid;

    bool _is_finished;

    std::string _filename;
};