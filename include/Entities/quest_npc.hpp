#pragma once

#include <array>

#include "npc.hpp"
#include "quest.hpp"

template<int questNum>
class QuestNPC : public  NPC {
public:
    void render() override {}

private:
    std::array<Quest,N> _quests;
};