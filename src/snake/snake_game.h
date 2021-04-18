#pragma once

#include "pch.h"

#include "snake.h"
#include "apple.h"

class SnakeGame
{
public:
    SnakeGame();

    void Update();
    bool IsRunning() const;

    Snake& GetSnake();
    Apple& GetApple();

    int GetID() const;

private:
    Snake snake;
    Apple apple;

    int id { 0 };
    void GiveID();
};