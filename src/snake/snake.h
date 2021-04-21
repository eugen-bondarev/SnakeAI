#pragma once

#include "cell.h"
#include "field.h"
#include "apple.h"

#include "ai/genetic/genome.h"

class Snake : public Genome
{
public:
    Snake(Cell head = { rand() % FIELD_SIZE, rand() % FIELD_SIZE });

    void Update();
    void Draw(Field& field) const;
    bool IsAlive() const;
    void Reset();

    Cell& GetHead();
    Cell& GetLastCell();
    Apple& GetApple();

    int GetID() const;

    enum class Direction { Up = 0, Left, Down, Right };
    std::map<Direction, Cell> moves = {
        { Direction::Up,    Cell( 0, -1) },
        { Direction::Left,  Cell(-1,  0) },
        { Direction::Down,  Cell( 0,  1) },
        { Direction::Right, Cell( 1,  0) },
    };

    void SetDirection(Direction _direction);
    void Control(bool up, bool left, bool down, bool right);
    float GetFitness() const override;

private:
    int id { 0 };
    std::vector<RenderableCell> cells;
    Direction direction { static_cast<Direction>(rand() % 4) };
    Apple apple;    
    bool alive { true };
    int age { 0 };
    int amountOfTurns { 0 };

    int GetDistanceToUpWall();
    int GetDistanceToLeftWall();
    int GetDistanceToDownWall();
    int GetDistanceToRightWall();
    int GetDistanceToAppleX();
    int GetDistanceToAppleY();
    
    bool DirectionIsValid(Direction newDirection);
    void SaveLastPositionOfCells();
    void Decide();
    void MoveHead();
    void Clamp();
    void MoveTail();
    void IfEatingApple();
    void AddTail();
};