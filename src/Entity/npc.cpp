#include "npc.hpp"

NPC::NPC(const std::array<Texture2D,DIRECTIONS_COUNT>& textures, const Vector2 & position)
: InteractiveObject(textures) {
    _position = position;
}


NPC::NPC(const std::array<Texture2D,DIRECTIONS_COUNT>& textures, const Vector2 & position, std::function<void()> interact)
: InteractiveObject(textures,100.0f,interact) {
    _position = position;
}

void NPC::setName(const std::string& name) {
    _name = name;
}

void NPC::addPhrase(const std::string& phrase) {
    _phrases.push_back(phrase);
}

void NPC::setPhrases(const std::vector<std::string> &phrases){

}

void NPC::setScript(const std::function<void()> script) { 
    _script = script;
}

const std::string &NPC::sayRandomPhrase() {
    return _phrases[_ds(_mt)];
}

void NPC::update() {
    _script();
}