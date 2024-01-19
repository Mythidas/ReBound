#include "rbpch.h"
#include "OGL_ImGUILayer.h"
#include "RBEngine/Core/Application.h"

#include <misc/cpp/imgui_stdlib.cpp>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <imgui.h>
#include <ImGuizmo.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace RB::OGL
{
	OGL_ImGUILayer::OGL_ImGUILayer(const Builder& builder)
		: Layer("ImGUILayer")
	{
		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::Get().GetWindow()->GetNativeWindow()), true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	OGL_ImGUILayer::~OGL_ImGUILayer()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void OGL_ImGUILayer::BeginUI()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	}

	void OGL_ImGUILayer::EndUI()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)Application::Get().GetWindow()->GetWidth(), (float)Application::Get().GetWindow()->GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}