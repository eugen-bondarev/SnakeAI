#include "snake.h"

Snake::Snake(Cell head) : Genome({ 10, 28, 26, 4 }), cells { { head } }
{
    static int ids { 0 };
    id = ids++;
}

void Snake::SetStatistics(GameStatistics* statistics)
{
    statistics->averageFitness += GetFitness();
    statistics->averageScore += cells.size();
    
    if (GetFitness() > statistics->bestFitness)
    {
        statistics->bestFitness = GetFitness();
    }

    if (cells.size() > statistics->bestScore)
    {
        statistics->bestScore = cells.size();
    }
    
    if (GetFitness() > statistics->bestFitnessOfPopulation)
    {
        statistics->bestFitnessOfPopulation = GetFitness();
    }

    if (cells.size() > statistics->bestScoreOfPopulation)
    {
        statistics->bestScoreOfPopulation = cells.size();
    }
}

bool Snake::EatsItself()
{
    for (int i = 1; i < cells.size(); i++)
    {
        if (cells[0].x == cells[i].x && cells[0].y == cells[i].y)
        {
            return true;
        }
    }

    return false;
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
    auto distanceToTail = DistanceToTail();
    std::vector<float> input = {
        static_cast<float>(GetDistanceToUpWall())    / static_cast<float>(FIELD_SIZE),
        static_cast<float>(GetDistanceToDownWall())  / static_cast<float>(FIELD_SIZE),
        static_cast<float>(GetDistanceToLeftWall())  / static_cast<float>(FIELD_SIZE),
        static_cast<float>(GetDistanceToRightWall()) / static_cast<float>(FIELD_SIZE),

        distanceToTail[0],
        distanceToTail[1],
        distanceToTail[2],
        distanceToTail[3],

        static_cast<float>(GetDistanceToAppleX())    / static_cast<float>(FIELD_SIZE),
        static_cast<float>(GetDistanceToAppleY())    / static_cast<float>(FIELD_SIZE)
    };

    auto result = neuralNetwork.Feed(input);

    float maxValue = -1.0f;
    int maxIndex = 0;

    for (int i = 0; i < result.size(); i++)
    {
        if (result[i] > maxValue)
        {
            maxValue = result[i];
            maxIndex = i;
        }
    }

    Direction newDirection = static_cast<Direction>(maxIndex);

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
        movesLeft = maxAmountOfMoves;
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

std::array<float, 4> Snake::DistanceToTail()
{    
    std::array<float, 4> result;

    result[0] = -1;
    result[1] = -1;
    result[2] = -1;
    result[3] = -1;

    for (int i = 1; i < cells.size(); i++)
    {
        if (cells[i].y == cells[0].y)
        {
            if (cells[i].x < cells[0].x)
            {
                result[0] = (cells[0].x - cells[i].x) / FIELD_SIZE;
            }

            if (cells[i].x > cells[0].x)
            {
                result[1] = (cells[i].x - cells[0].x) / FIELD_SIZE;
            }
        }

        if (cells[i].x == cells[0].x)
        {
            if (cells[i].y > cells[0].y)
            {
                result[2] = (cells[i].y - cells[0].y) / FIELD_SIZE;
            }

            if (cells[i].y < cells[0].y)
            {
                result[3] = (cells[0].y - cells[i].y) / FIELD_SIZE;
            }
        }
    }

    return result;
}

void Snake::Clamp()
{
    if (EatsItself())
    {
        alive = false;
    }

    for (const auto& cell : cells)
    {
        int x = cell.x;
        int y = cell.y;

        if (x < 0 || x >= FIELD_SIZE || y < 0 || y >= FIELD_SIZE || movesLeft <= 0)
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
    movesLeft -= 1;
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
    return static_cast<float>(cells.size()) + static_cast<float>(age) / 1000.0f;
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