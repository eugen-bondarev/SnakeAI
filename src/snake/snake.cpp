#include "snake.h"

Snake::Snake(Cell head) : cells { { head } }
{
    dir = static_cast<Direction>(rand() % 4);
}

void Snake::Update()
{
    switch (dir)
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

Cell& Snake::GetHead()
{
    return cells[0];
}