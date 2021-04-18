#pragma once

#include "cell.h"
#include "field.h"

class Snake
{
public:
    Snake(Cell head = { rand() % FIELD_SIZE, rand() % FIELD_SIZE });

    void Update();
    void Draw(Field& field) const;
    void AddTail();
    bool IsAlive() const;
    void Reset();

    Cell& GetHead();
    Cell& GetLastCell();

    enum class Direction { Up = 0, Left, Down, Right };
    std::map<Direction, Cell> moves = {
        { Direction::Up,    Cell( 0, -1) },
        { Direction::Left,  Cell(-1,  0) },
        { Direction::Down,  Cell( 0,  1) },
        { Direction::Right, Cell( 1,  0) },
    };

    void SetDirection(Direction _direction);
    void Control(bool up, bool left, bool down, bool right);

private:
    std::vector<RenderableCell> cells;
    Direction direction { static_cast<Direction>(rand() % 4) };
    bool alive { true };

    void SaveLastPositionOfCells();
    void MoveHead();
    void Clamp();
    void MoveTail();
};