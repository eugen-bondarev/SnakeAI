#pragma once

#include "imgui/imgui.h"

struct Cell
{
    int x { 0 };
    int y { 0 };

    int lastX { 0 };
    int lastY { 0 };

    Cell(int _x, int _y) : x { _x }, y { _y } {}
    Cell() {}

    bool operator==(const Cell& other) const;
};

struct RenderableCell : public Cell
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

    RenderableCell(int _x, int _y) : Cell(_x, _y) {}
    RenderableCell(Cell cell) : Cell(cell.x, cell.y) {}
    RenderableCell() {}
};