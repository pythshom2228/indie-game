#pragma once
#include "entity.hpp"
#include <Interactive/interactivable.hpp>
#include <vector>
#include <string>
#include <random>


class NPC : public InteractiveObject {
public:

    NPC(const std::array<Texture2D,DIRECTIONS_COUNT>& textures, const Vector2 & position);

    NPC(const std::array<Texture2D,DIRECTIONS_COUNT>& textures, const Vector2 & position, std::function<void()> interact);

    ~NPC() = default;

    void setName(const std::string& name);

    void addPhrase(const std::string& phrase);

    void setPhrases(const std::vector<std::string>& phrases);
    void setScript(const std::function<void()> script);

    const std::string& sayRandomPhrase();

    void update();

protected:

    std::string _name;
    std::vector<std::string> _phrases;

    std::function<void()> _script = [](){};
private:
    std::mt19937 _mt{42};
    std::uniform_int_distribution<size_t> _ds{0,_phrases.size()};
};