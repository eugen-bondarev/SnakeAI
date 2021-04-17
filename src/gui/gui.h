#pragma once

#include "window/window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class GUI
{
public:
    GUI(Window& window);

    void NewFrame() const;
    void Render() const;

    ~GUI();

private:
    Window& window;

    GUI(const GUI&) = delete;
    GUI& operator=(const GUI&) = delete;
};