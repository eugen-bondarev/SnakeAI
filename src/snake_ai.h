#pragma once

#include "snake/field.h"
#include "snake/snake.h"

#include "window/window.h"

#include "ai/genetic/population.h"

struct GameSettings
{
    float speed { 4.0f };
    bool forceFullSpeed { true };
};

class SnakeAI
{
public:
    SnakeAI(Window& window);

    void Update();

private:
    Window& window;
    
    GameSettings settings;

    Field field;

    std::unique_ptr<Population<Snake>> population;
};