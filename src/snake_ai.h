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

    struct {
        int amountOfGenomes { 5000 };
        float selection { 8.0f };
        bool running { true };
        std::unique_ptr<Population<Snake>> population;
    } simulation;

    void RenderSimulationSettings();
    
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


    void UpdatePopulation();
    void RenderGames();
};