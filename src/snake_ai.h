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
    
    GameStatistics statistics;

    void RenderStatistics();

    struct {
        float speed { 4.0f };
        bool forceFullSpeed { true };
    } settings;

    void RenderSettings();

    struct {
        int border { 10 };
        int cellSize { 18 };
        int padding { 0 };
        bool geneticSnakeColor { false };
    } visual;

    void RenderVisualSettings();

    Field field;

    std::unique_ptr<Population<Snake>> population;

    void UpdatePopulation();
    void RenderGames();
};