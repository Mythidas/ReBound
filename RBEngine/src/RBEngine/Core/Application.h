#pragma once

#include "Defines.h"
#include "Window.h"
#include "LayerStack.h"
#include "Input.h"
#include "RBEngine/Rendering/RenderCommands.h"
#include "RBEngine/ImGUI/ImGUILayer.h"
#include "RBEngine/Utils/Singleton.h"

namespace RB
{
	class Application : public Singleton<Application>
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
		void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

		void PopLayer(Layer* layer) { m_LayerStack.PopLayer(layer); }
		void PopOverlay(Layer* overlay) { m_LayerStack.PopOverlay(overlay); }

		static Scope<Window>& GetWindow() { return Get().m_Window; }

	private:
		bool OnWindowClose();
		bool OnWindowResize(int width, int height);

	private:
		Scope<Window> m_Window;
		Scope<Input> m_Input;
		Scope<RenderCommands> m_RenderCommands;
		Ref<ImGUILayer> m_ImGUILayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	static Application* CreateApplication();
}