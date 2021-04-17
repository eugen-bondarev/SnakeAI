#include <iostream>

#include "window/window.h"
#include "gui/gui.h"

int main()
{
    Window window;
    GUI gui(window);

    while (!window.ShouldClose())
    {
        window.PollEvents();

        gui.NewFrame();

        ImGui::ShowDemoWindow();

        gui.Render();

        window.SwapBuffers();
    }

    return 0;
}