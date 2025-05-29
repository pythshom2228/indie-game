#pragma once
#include "npc.hpp"
#include "array"
#include "quest.hpp"

template<int questNum>
class QuestNPC : NPC {
public:
    void render() override {}

private:
    std::array<Quest,N> _quests;
};