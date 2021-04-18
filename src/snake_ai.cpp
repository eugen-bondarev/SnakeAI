#include "snake_ai.h"

#include "ai/neural_network.h"

SnakeAI::SnakeAI(Window& _window) : window { _window }
{
    static int initialAmountOfGames { 5 };
    games.resize(initialAmountOfGames);
}

void SnakeAI::Update()
{
    ImGui::Begin("Game settings");
        // Speed of updating the field.
        ImGui::DragFloat("Speed", &gameSpeed, 0.01f, 0.2f, 100.0f);

        // List of all the games.
        if (ImGui::CollapsingHeader("Games"))
        {
            if (ImGui::Button("Reborn all"))
            {
                for (auto& game : games)
                {
                    game.Reborn();
                }
            }

            for (int i = 0; i < games.size(); i++)
            {
                SnakeGame& game = games[i];

                std::string label = "#" + std::to_string(game.GetID());
                ImGui::AlignTextToFramePadding();
                ImGui::Text(label.c_str()); ImGui::SameLine();

                if (ImGui::Button(("Reborn##" + std::to_string(i)).c_str()))
                {
                    game.Reborn();
                }
            }
        }

    ImGui::End();

    ImGui::Begin("Drawing", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGuiUtil::winRect.Update();
    
    static float timer { 0 };

    timer += window.GetDeltaTime();
    if (timer >= 0.2f /* default speed factor */ * (1.0f / gameSpeed))
    {
        for (auto& game : games)
        {
            if (game.IsRunning())
            {
                game.Update();
            }
        }
            
        timer = 0;
    }

    // If we want to control one of the snakes (for example to test its behaviour).
    // if (games.size())
    // {
    //     bool up = ImGui::IsKeyDown(GLFW_KEY_W);
    //     bool left = ImGui::IsKeyDown(GLFW_KEY_A);
    //     bool down = ImGui::IsKeyDown(GLFW_KEY_S);
    //     bool right = ImGui::IsKeyDown(GLFW_KEY_D);
    //     games[0].GetSnake().Control(up, left, down, right);
    // }

    field.Clear();

    for (auto& game : games)
    {
        if (game.IsRunning())
        {
            game.GetSnake().Draw(field);
            game.GetApple().Draw(field);
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