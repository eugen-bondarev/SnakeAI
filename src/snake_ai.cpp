#include "snake_ai.h"

SnakeAI::SnakeAI(Window& _window) : window { _window }
{
}

void SnakeAI::Update()
{
    ImGui::Begin("Drawing", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    ImGuiUtil::winRect.Update();
    
    static float timer { 0 };

    timer += window.GetDeltaTime();
    if (timer >= 1.0f)
    {
        snake.Update();
        timer = 0;
    }

    field.Clear();
    snake.Draw(field);

    for (int x = 0; x < Field::SIZE; x++)
    {
        for (int y = 0; y < Field::SIZE; y++)
        {
            float minX = ImGuiUtil::winRect.min.x + x * RenderableCell::SIZE + RenderableCell::PADDING;
            float minY = ImGuiUtil::winRect.min.y + y * RenderableCell::SIZE + RenderableCell::PADDING;
            float maxX = ImGuiUtil::winRect.min.x + (x + 1) * RenderableCell::SIZE;
            float maxY = ImGuiUtil::winRect.min.y + (y + 1) * RenderableCell::SIZE;

            drawList->AddRectFilled(ImVec2(minX, minY), ImVec2(maxX, maxY), field[x][y].GetColor());
        }
    }

    ImGui::End();
}