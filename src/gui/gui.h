#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void Style1(ImGuiStyle& s);

class GUI
{
public:
    GUI(GLFWwindow* glfwWindow);

    void NewFrame() const;
    void Render() const;

    ~GUI();

private:
    GLFWwindow* glfwWindow;

    GUI(const GUI&) = delete;
    GUI& operator=(const GUI&) = delete;
};

namespace ImGuiUtil {

struct WindowRect
{
    ImVec2 min;
    ImVec2 max;

    void Update();

} inline static winRect;

}