#pragma once
#include <raylib.h>
#define RES_PATH "../resources/"

extern const Font game_font;

enum RotationStates {
    Up = 0,
    Right = 1,
    Down = 2,
    Left = 4
};