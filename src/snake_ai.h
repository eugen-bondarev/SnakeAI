#pragma once

#include "snake/field.h"
#include "snake/snake.h"

#include "window/window.h"

class SnakeAI
{
public:
    SnakeAI(Window& window);

    void Update();

private:
    Window& window;

    Field field;
    Snake snake;

};