#pragma once

#include "imgui/imgui.h"

struct Cell
{
    int x { 0 };
    int y { 0 };
};

struct RenderableCell : Cell
{
    enum class State
    {
        Empty,
        Snake,
        Apple
    };

    State state { State::Empty };

    ImU32 GetColor();

    inline static constexpr unsigned int SIZE = 12;
    inline static constexpr unsigned int PADDING = 1;
};