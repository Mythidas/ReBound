#pragma once

#include "Defines.h"
#include "Window.h"
#include "LayerStack.h"
#include "Input.h"
#include "Project.h"
#include "RBEngine/Rendering/RenderCommands.h"
#include "RBEngine/Reflection/Domain.h"
#include "RBEngine/ImGUI/ImGUILayer.h"
#include "RBEngine/Utils/Singleton.h"
#include "RBEngine/Utils/Bit.h"

namespace RB
{
	class Application : public Singleton<Application>
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Close();

		void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
		void PopLayer(Layer* layer) { m_LayerStack.PopLayer(layer); }

	public:
		static Scope<Window>& GetWindow() { return Get().m_Window; }
		static const uint32_t VERSION = Bit::U32_4x8(0, 0, 1, 0);

	private:
		bool OnWindowClose();
		bool OnWindowResize(int width, int height);

	private:
		Scope<Window> m_Window;
		Scope<Input> m_Input;
		Scope<Domain> m_Domain;
		Scope<RenderCommands> m_RenderCommands;
		Ref<ImGUILayer> m_ImGUILayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	static Application* CreateApplication();
}