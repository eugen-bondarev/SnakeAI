#include "gui.h"

#include <GLFW/glfw3.h>

GUI::GUI(GLFWwindow* _glfwWindow) : glfwWindow { _glfwWindow }
{   
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init();
}

void GUI::NewFrame() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	window_flags |= 
					ImGuiWindowFlags_NoTitleBar 
					| ImGuiWindowFlags_NoCollapse 
					| ImGuiWindowFlags_NoResize 
					| ImGuiWindowFlags_NoMove;
					
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	static bool leave_open = true;
	ImGui::Begin("ENGINE_FULL_NAME", &leave_open, ImGuiWindowFlags_NoTitleBar);
	static int dockspace_id = ImGui::GetID("HUB_DockSpace");
	ImGui::DockSpace(dockspace_id , ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
	ImGui::End();
}

void GUI::Render() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		glfwMakeContextCurrent(backup_current_context);
	}
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