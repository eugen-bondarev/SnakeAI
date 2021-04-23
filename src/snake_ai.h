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
    GameStatistics statistics;

    Field field;

    struct {
        int border { 10 };
        int cellSize { 18 };
        int padding { 0 };
        bool geneticSnakeColor { false };
    } visual;

    std::unique_ptr<Population<Snake>> population;
};