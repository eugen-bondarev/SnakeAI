#include "snake_ai.h"

#include "ai/neural_network.h"

SnakeAI::SnakeAI(Window& _window) : window { _window }
{
}

void SnakeAI::RenderSimulationSettings()
{
    ImGui::Begin("Simulation settings");
        ImGui::PushItemWidth(100);
        ImGui::DragInt("Amount of genomes", &simulation.amountOfGenomes, 1.0f, 10, 10000);
        ImGui::DragFloat("Selection (%)", &simulation.selection, 0.1f, 10, 10000);
        ImGui::PopItemWidth();
        if (!simulation.population)
        {
            if (ImGui::Button("Create", ImVec2(100, 18)))
            {
                simulation.population = std::make_unique<Population<Snake>>(simulation.amountOfGenomes);
            }
        }
        else
        {
            if (ImGui::Button(simulation.running ? "Pause" : "Play", ImVec2(100, 18)))
            {
                simulation.running = !simulation.running;
            }

            ImGui::SameLine();

            if (ImGui::Button("Destroy"))
            {
                simulation.population.reset();
            }
        }
    ImGui::End();
}

void SnakeAI::RenderStatistics()
{
    ImGui::Begin("Statistics");
        if (simulation.population)
            ImGui::Text(("Generation: "        + std::to_string(simulation.population->GetGeneration())).c_str());

        ImGui::Text(("Best fitness: "      + std::to_string(statistics.bestFitness)).c_str());
        ImGui::Text(("Best score: "        + std::to_string(statistics.bestScore)).c_str());
        ImGui::Text(("Best fitness pop.: " + std::to_string(statistics.bestFitnessOfPopulation)).c_str());
        ImGui::Text(("Best score pop.: "   + std::to_string(statistics.bestScoreOfPopulation)).c_str());
        ImGui::Text(("Av. fitness: "       + std::to_string(statistics.averageFitness)).c_str());
        ImGui::Text(("Av. score: "         + std::to_string(statistics.averageScore)).c_str());
    ImGui::End();
}

void SnakeAI::RenderVisualSettings()
{    
    ImGui::Begin("Visual");
        ImGui::Checkbox("Genetic snake color", &visual.geneticSnakeColor);
    ImGui::End();
}

void SnakeAI::RenderSettings()
{
    ImGui::Begin("Game settings");
        ImGui::DragFloat("Speed", &settings.speed, 0.01f, 0.2f, 100.0f);
        ImGui::Checkbox("Force full speed", &settings.forceFullSpeed);

        if (ImGui::CollapsingHeader("Games"))
        {
            if (ImGui::Button("Reborn all"))
            {
                for (auto& game : simulation.population->GetGenomes())
                {
                    game->Reset();
                }
            }

            for (int i = 0; i < simulation.population->GetGenomes().size(); i++)
            {
                Snake& game = *simulation.population->GetGenomes()[i];

                std::string label = "#" + std::to_string(game.GetID());
                ImGui::AlignTextToFramePadding();
                ImGui::Text(label.c_str()); ImGui::SameLine();

                if (ImGui::Button(("Reborn##" + std::to_string(i)).c_str()))
                {
                    game.Reset();
                }
            }
        }
    ImGui::End();
}

void SnakeAI::UpdatePopulation()
{
    static float updateTimer { 0 };

    updateTimer += window.GetDeltaTime();
    if (simulation.running && (settings.forceFullSpeed || updateTimer >= 0.2f * (1.0f / settings.speed)))
    {
        bool populationIsAlive { false };

        statistics.averageFitness = 0;
        statistics.averageScore = 0;
        statistics.bestFitnessOfPopulation = 0;
        statistics.bestScoreOfPopulation = 0;

        for (auto& game : simulation.population->GetGenomes())
        {
            game->SetStatistics(&statistics);

            if (game->IsAlive())
            {
                game->Update();

                populationIsAlive = true;
            }
        }

        statistics.averageFitness /= simulation.population->GetGenomes().size();
        statistics.averageScore /= simulation.population->GetGenomes().size();

        if (!populationIsAlive)
        {
            simulation.population->Evolution(simulation.selection);
            simulation.population->Restart();
        }
            
        updateTimer = 0;
    }
}

void SnakeAI::RenderGames()
{   
    ImGui::Begin("Population", (bool*)0, ImGuiWindowFlags_NoCollapse);

    ImGuiUtil::winRect.Update();

    field.Clear();

    for (auto& game : simulation.population->GetGenomes())
    {
        if (game->IsAlive())
        {
            game->Draw(field);
            game->GetApple().Draw(field);
        }
    }

    static ImU32 borderColor = ImU32(ImColor(ImVec4(0.1f, 0.1f, 0.1f, 1.0f)));

    ImGui::GetWindowDrawList()->AddRectFilled(
        ImVec2(ImGuiUtil::winRect.min.x, ImGuiUtil::winRect.min.y),         
        ImVec2(ImGuiUtil::winRect.min.x + visual.border, ImGuiUtil::winRect.min.y + FIELD_SIZE * (visual.cellSize) + visual.border * 2), 
        borderColor
    );

    ImGui::GetWindowDrawList()->AddRectFilled(
        ImVec2(ImGuiUtil::winRect.min.x + FIELD_SIZE * (visual.cellSize) + visual.border, ImGuiUtil::winRect.min.y),         
        ImVec2(ImGuiUtil::winRect.min.x + FIELD_SIZE * (visual.cellSize) + visual.border * 2, ImGuiUtil::winRect.min.y + FIELD_SIZE * (visual.cellSize) + visual.border * 2), 
        borderColor
    );

    ImGui::GetWindowDrawList()->AddRectFilled(
        ImVec2( ImGuiUtil::winRect.min.x,  ImGuiUtil::winRect.min.y),         
        ImVec2(ImGuiUtil::winRect.min.x + FIELD_SIZE * (visual.cellSize) + visual.border * 2,ImGuiUtil::winRect.min.y + visual.border), 
        borderColor
    );

    ImGui::GetWindowDrawList()->AddRectFilled(
        ImVec2(ImGuiUtil::winRect.min.x, ImGuiUtil::winRect.min.y + FIELD_SIZE * (visual.cellSize) + visual.border),         
        ImVec2(ImGuiUtil::winRect.min.x + FIELD_SIZE * (visual.cellSize) + visual.border * 2,ImGuiUtil::winRect.min.y + FIELD_SIZE * (visual.cellSize) + visual.border * 2), 
        borderColor
    );

    for (int x = 0; x < FIELD_SIZE; x++)
    {
        for (int y = 0; y < FIELD_SIZE; y++)
        {
            float minX = ImGuiUtil::winRect.min.x + x * visual.cellSize + visual.padding + static_cast<float>(visual.border);
            float minY = ImGuiUtil::winRect.min.y + y * visual.cellSize + visual.padding + static_cast<float>(visual.border);
            float maxX = ImGuiUtil::winRect.min.x + (x + 1) * visual.cellSize + static_cast<float>(visual.border);
            float maxY = ImGuiUtil::winRect.min.y + (y + 1) * visual.cellSize + static_cast<float>(visual.border);

            ImVec4 color = field[x][y].color;

            static const int appleBorder = 6;
            switch (field[x][y].state)
            {
                case RenderableCell::State::Apple:
                    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(minX + appleBorder, minY + appleBorder), ImVec2(maxX - appleBorder, maxY - appleBorder), ImU32(ImColor(color)));
                    break;
                
                case RenderableCell::State::Snake:
                    if (visual.geneticSnakeColor)
                        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(minX, minY), ImVec2(maxX, maxY), ImU32(ImColor(color)));
                    else
                        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(minX, minY), ImVec2(maxX, maxY), ImU32(ImColor(Snake::DEFAULT_COLOR)));
                    break;
                
                case RenderableCell::State::Empty:
                    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(minX, minY), ImVec2(maxX, maxY), ImU32(ImColor(color)));
                    break;
            }
        }
    }

    ImGui::End();
}

void SnakeAI::Update()
{
    RenderSimulationSettings();
    RenderStatistics();
    RenderVisualSettings();
    RenderSettings();

    if (!simulation.population)
        return;

    UpdatePopulation();
    RenderGames();
}