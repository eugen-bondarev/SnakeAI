#pragma once

#include "pch.h"

#include "gui/gui.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    unsigned int width, height;

    Window(unsigned int width = 1024, unsigned int height = 768);

    bool ShouldClose() const;
    void PollEvents() const;
    void SwapBuffers() const;
    void Clear() const;
    
    void BeginFrame();
    void EndFrame();

    ~Window();

    GLFWwindow* GetGlfwWindow();
    float GetDeltaTime() const;

private:
    GLFWwindow* glfwWindow;

    std::unique_ptr<GUI> gui;

    void InitGlew();

    void InitGlfw();
    void ShutdownGlfw();

    void InitGui();

    struct {
        float current { 0 };
        float last { 0 };
        float delta { 0 };
    } time;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
};