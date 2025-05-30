#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <sstream>
#include <tmxlite/Map.hpp>

#include "player.hpp"
#include "tile.hpp"


class World {
public:
    
    World();
    World(const std::string & filename, Player * player = nullptr);
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
    
    int getTileId(int x, int y) const;
    const Tile& getTile(int x, int y) const;
    const Player * getPlayer() const;
    std::string getFilename() const;
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

    Texture2D _tileset;
    std::vector<Tile> _tiles; 
    std::vector<int> _grid;
    int _width;
    int _height;

    bool _is_finished;
    std::string _world_name;
    std::string _filename;
};