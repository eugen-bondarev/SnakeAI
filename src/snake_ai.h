#pragma once

#include "snake/field.h"
#include "snake/snake.h"
#include "snake/snake_game.h"

#include "window/window.h"

class SnakeAI
{
public:
    SnakeAI(Window& window);

    void Update();

private:
    Window& window;

    float gameSpeed = 1.0f;

    Field field;
    std::vector<SnakeGame> games;
};