#include "snake.h"

Snake::Snake(Cell head) : Genome({ 6, 18, 18, 1 }), cells { { head } }
{
    static int ids { 0 };
    id = ids++;
}

void Snake::Update()
{
    SaveLastPositionOfCells();

    Decide();

    MoveHead();
    Clamp();
    IfEatingApple();
    MoveTail();

    age += 1;
}

void Snake::Decide()
{
    std::vector<float> input = {
        static_cast<float>(GetDistanceToUpWall())    / FIELD_SIZE,
        static_cast<float>(GetDistanceToLeftWall())  / FIELD_SIZE,
        static_cast<float>(GetDistanceToDownWall())  / FIELD_SIZE,
        static_cast<float>(GetDistanceToRightWall()) / FIELD_SIZE,
        static_cast<float>(GetDistanceToAppleX())    / FIELD_SIZE,
        static_cast<float>(GetDistanceToAppleY())    / FIELD_SIZE
    };

    float result = neuralNetwork.Feed(input)[0];

    Direction newDirection = static_cast<Direction>(result * 4.0f);

    if (DirectionIsValid(newDirection))
    {
        SetDirection(newDirection);
    }
}

void Snake::IfEatingApple()
{
    if (GetHead() == apple)
    {
        AddTail();
        apple = Apple();
    }
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

int Snake::GetDistanceToUpWall()
{
    return cells[0].y;
}

int Snake::GetDistanceToLeftWall()
{
    return cells[0].x;
}

int Snake::GetDistanceToDownWall()
{
    return FIELD_SIZE - cells[0].y;
}

int Snake::GetDistanceToRightWall()
{
    return FIELD_SIZE - cells[0].x;
}

int Snake::GetDistanceToAppleX()
{
    return cells[0].x - apple.x;
}

int Snake::GetDistanceToAppleY()
{
    return cells[0].y - apple.y;
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

bool Snake::DirectionIsValid(Direction newDirection)
{
    if (direction == newDirection)                                         return false;

    if (direction == Direction::Left  && newDirection != Direction::Right) return true;
    if (direction == Direction::Right && newDirection != Direction::Left)  return true;
    if (direction == Direction::Up    && newDirection != Direction::Down)  return true;
    if (direction == Direction::Down  && newDirection != Direction::Up)    return true;

    return false;
}

void Snake::SetDirection(Direction newDirection)
{
    direction = newDirection;
    amountOfTurns += 1;
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

float Snake::GetFitness() const
{
    return static_cast<float>(cells.size());
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

Apple& Snake::GetApple()
{
    return apple;
}

int Snake::GetID() const
{
    return id;
}