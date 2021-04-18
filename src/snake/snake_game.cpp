#include "snake_game.h"

SnakeGame::SnakeGame()
{
    GiveID();
}

void SnakeGame::Update()
{
    snake.Update();

    if (snake.GetHead() == apple)
    {
        snake.AddTail();
        apple = Apple();
    }
}

bool SnakeGame::IsRunning() const
{
    return snake.IsAlive();
}

void SnakeGame::Reborn()
{
    snake.Reset();
    apple = Apple();
}

Snake& SnakeGame::GetSnake()
{
    return snake;
}

Apple& SnakeGame::GetApple()
{
    return apple;
}

void SnakeGame::GiveID()
{
    static int ids { 0 };
    id = ids++;
}

int SnakeGame::GetID() const
{
    return id;
}