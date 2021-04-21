#include "snake_ai.h"

#include "ai/neural_network.h"

SnakeAI::SnakeAI(Window& _window) : window { _window }
{
    // 2000 to 5000 is an optimal number for this particular game.
    static int initialAmountOfGames { 2000 };
    population = std::make_unique<Population<Snake>>(initialAmountOfGames);
}

void SnakeAI::Update()
{
    ImGui::Begin("Statistics");
        ImGui::Text(("Generation: "   + std::to_string(population->GetGeneration())).c_str());
        ImGui::Text(("Best fitness: " + std::to_string(statistics.bestFitness)).c_str());
        ImGui::Text(("Best score: "   + std::to_string(statistics.bestScore)).c_str());
        ImGui::Text(("Best fitness pop.: " + std::to_string(statistics.bestFitnessOfPopulation)).c_str());
        ImGui::Text(("Best score pop.: "   + std::to_string(statistics.bestScoreOfPopulation)).c_str());
        ImGui::Text(("Av. fitness: "  + std::to_string(statistics.averageFitness)).c_str());
        ImGui::Text(("Av. score: "    + std::to_string(statistics.averageScore)).c_str());
    ImGui::End();

    ImGui::Begin("Game settings");
        // Speed of updating the field.
        ImGui::DragFloat("Speed", &settings.speed, 0.01f, 0.2f, 100.0f);

        ImGui::Checkbox("Force full speed", &settings.forceFullSpeed);

        // List of all the games.
        if (ImGui::CollapsingHeader("Games"))
        {
            if (ImGui::Button("Reborn all"))
            {
                for (auto& game : population->GetGenomes())
                {
                    game->Reset();
                }
            }

            for (int i = 0; i < population->GetGenomes().size(); i++)
            {
                Snake& game = *population->GetGenomes()[i];

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

    ImGui::Begin("Drawing", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGuiUtil::winRect.Update();
    
    static float timer { 0 };

    timer += window.GetDeltaTime();
    if (settings.forceFullSpeed || timer >= 0.2f * (1.0f / settings.speed))
    {
        bool populationIsAlive { false };

        statistics.averageFitness = 0;
        statistics.averageScore = 0;
        statistics.bestFitnessOfPopulation = 0;
        statistics.bestScoreOfPopulation = 0;

        for (auto& game : population->GetGenomes())
        {
            game->SetStatistics(&statistics);

            if (game->IsAlive())
            {
                game->Update();

                populationIsAlive = true;
            }
        }

        statistics.averageFitness /= population->GetGenomes().size();
        statistics.averageScore /= population->GetGenomes().size();

        if (!populationIsAlive)
        {
            population->Evolution();
            population->Restart();
        }
            
        timer = 0;
    }

    field.Clear();

    for (auto& game : population->GetGenomes())
    {
        if (game->IsAlive())
        {
            game->Draw(field);
            game->GetApple().Draw(field);
        }
    }

    for (int x = 0; x < FIELD_SIZE; x++)
    {
        for (int y = 0; y < FIELD_SIZE; y++)
        {
            float minX = ImGuiUtil::winRect.min.x + x * RenderableCell::SIZE + RenderableCell::PADDING;
            float minY = ImGuiUtil::winRect.min.y + y * RenderableCell::SIZE + RenderableCell::PADDING;
            float maxX = ImGuiUtil::winRect.min.x + (x + 1) * RenderableCell::SIZE;
            float maxY = ImGuiUtil::winRect.min.y + (y + 1) * RenderableCell::SIZE;

            ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(minX, minY), ImVec2(maxX, maxY), field[x][y].GetColor());
        }
    }

    ImGui::End();
}