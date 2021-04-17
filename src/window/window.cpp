#include "window.h"

Window::Window(unsigned int width_param, unsigned int height_param) : width { width_param }, height { height_param }
{
    InitGlew();
    InitGlfw();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(glfwWindow);
}

void Window::PollEvents() const
{
    glfwPollEvents();
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(glfwWindow);
}

Window::~Window()
{
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

void Window::InitGlew()
{
    glewInit();
}

void Window::InitGlfw()
{
    glfwInit();

    glfwWindow = glfwCreateWindow(width, height, "SnakeAI", nullptr, nullptr);
    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(1);
}