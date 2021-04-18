#include "snake.h"

Snake::Snake(Cell head) : cells { { head } }
{
}

void Snake::Update()
{
    SaveLastPositionOfCells();
    MoveHead();
    Clamp();
    MoveTail();
}

void Snake::MoveHead()
{
    GetHead().x += moves[direction].x;
    GetHead().y += moves[direction].y;
}

void Snake::SaveLastPositionOfCells()
{
    for (auto& cell : cells)
    {
        cell.lastX = cell.x;
        cell.lastY = cell.y;
    }
}

void Snake::MoveTail()
{
    for (int i = 1; i < cells.size(); i++)
    {
        Cell& lastCell = cells[i - 1];
        cells[i].x = lastCell.lastX;
        cells[i].y = lastCell.lastY;
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

void Snake::AddTail()
{
    Cell& lastCell = GetLastCell();
    int x = lastCell.x;
    int y = lastCell.y;

    RenderableCell cell = RenderableCell(x, y);
    
    cells.emplace_back(cell);
}

void Snake::Clamp()
{
    for (const auto& cell : cells)
    {
        int x = cell.x;
        int y = cell.y;

        if (x < 0 || x >= FIELD_SIZE || y < 0 || y >= FIELD_SIZE)
        {
            alive = false;
            break;
        }
    }
}

void Snake::SetDirection(Direction _direction)
{
    direction = _direction;
}

void Snake::Control(bool up, bool left, bool down, bool right)
{
    if (up)    SetDirection(Snake::Direction::Up);
    if (left)  SetDirection(Snake::Direction::Left);
    if (down)  SetDirection(Snake::Direction::Down);
    if (right) SetDirection(Snake::Direction::Right);
}

void Snake::Reset()
{
    cells.clear();
    cells.emplace_back(Cell(rand() % FIELD_SIZE, rand() % FIELD_SIZE));
    alive = true;
    direction = static_cast<Direction>(rand() % 4);
}

bool Snake::IsAlive() const
{
    return alive;
}

Cell& Snake::GetHead()
{
    return cells[0];
}

Cell& Snake::GetLastCell()
{
    return cells[cells.size() - 1];
}