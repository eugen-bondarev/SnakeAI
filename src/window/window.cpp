#include "window.h"

Window::Window(unsigned int width_param, unsigned int height_param) : width { width_param }, height { height_param }
{
    InitGlfw();
    InitGlew();
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

void Window::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
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

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, "SnakeAI", nullptr, nullptr);
    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(1);
    glfwShowWindow(glfwWindow);
    glfwMaximizeWindow(glfwWindow);
}

GLFWwindow* Window::GetGlfwWindow()
{
    return glfwWindow;
}