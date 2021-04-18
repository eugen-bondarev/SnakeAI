#pragma once

#include "cell.h"
#include "field.h"

class Snake
{
public:
    Snake(Cell head = { rand() % Field::SIZE, rand() % Field::SIZE });

    void Update();
    void Draw(Field& field) const;

    bool IsAlive() const;

    Cell& GetHead();

    enum class Direction
    {
        Top = 0,
        Left,
        Down,
        Right
    };

private:
    std::vector<RenderableCell> cells;
    Direction direction { static_cast<Direction>(rand() % 4) };
    bool alive { true };

    void Clamp();
};