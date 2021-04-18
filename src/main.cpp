#include <iostream>

#include "window/window.h"
#include "gui/gui.h"

#include "snake/field.h"
#include "snake/snake.h"

int main()
{
    Window window;
    
    InitRandomEngine();

    Field field;
    Snake snake;

    while (!window.ShouldClose())
    {
        window.BeginFrame();

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
        
        window.EndFrame();
    }

    return 0;
}