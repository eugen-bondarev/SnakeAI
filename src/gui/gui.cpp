#include "gui.h"

GUI::GUI(GLFWwindow* _glfwWindow) : glfwWindow { _glfwWindow }
{   
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init();
}

void GUI::NewFrame() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::Render() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiUtil::WindowRect::Update()
{
    min = ImGui::GetWindowContentRegionMin();
    max = ImGui::GetWindowContentRegionMax();

    min.x += ImGui::GetWindowPos().x;
    min.y += ImGui::GetWindowPos().y;
    max.x += ImGui::GetWindowPos().x;
    max.y += ImGui::GetWindowPos().y;
}