#pragma once

#include "pch.h"

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

    ~Window();

    GLFWwindow* GetGlfwWindow();

private:
    GLFWwindow* glfwWindow;

    void InitGlew();
    void InitGlfw();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
};