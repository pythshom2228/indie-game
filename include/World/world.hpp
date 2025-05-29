#pragma once

class World {
public:
    Player* _player;
    std::vector<Entity> _entities;
    Texture2D _background;
    bool _isFinished;
private:
    void render() const;

    void loadFromFile(const std::string & filename);
    bool isColidable(int x, int y);
    
};