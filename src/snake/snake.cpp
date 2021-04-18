#include "snake.h"

Snake::Snake(Cell head) : cells { { head } }
{
}

void Snake::Update()
{
    switch (direction)
    {
        case Direction::Top:
            GetHead().y -= 1;
            break;

        case Direction::Left:
            GetHead().x -= 1;
            break;

        case Direction::Down:
            GetHead().y += 1;
            break;

        case Direction::Right:
            GetHead().x += 1;
            break;
    }

    Clamp();
}

void Snake::Draw(Field& field) const
{
    for (const auto& cell : cells)
    {
        int x = cell.x;
        int y = cell.y;

        field[x][y].state = RenderableCell::State::Snake;
    }
}

void Snake::Clamp()
{
    for (const auto& cell : cells)
    {
        int x = cell.x;
        int y = cell.y;

        if (x < 0 || x > Field::SIZE || y < 0 || y > Field::SIZE)
        {
            alive = false;
            break;
        }
    }
}

bool Snake::IsAlive() const
{
    return alive;
}

Cell& Snake::GetHead()
{
    return cells[0];
}