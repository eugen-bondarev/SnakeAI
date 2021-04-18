#pragma once

#include "snake/field.h"
#include "snake/snake.h"

#include "window/window.h"

#include "ai/genetic/population.h"

class SnakeAI
{
public:
    SnakeAI(Window& window);

    void Update();

private:
    Window& window;

    float gameSpeed = 1.0f;

    Field field;

    std::unique_ptr<Population<Snake>> population;
};