#include "rbpch.h"
#include "Application.h"

#include "Time.h"
#include "RBEngine/Debug/Log.h"
#include "RBEngine/Rendering/Renderer.h"

namespace RB
{
	Application::Application()
	{
		Log::Construct();
		Time::Construct();
		
		m_Input = CreateScope<Input>();
		m_Window = Window::Builder().setFixedAspectRatio(true).setTitle("ReBound").setWidth(1280).setHeight(720).Build();

		Renderer::Construct();

		Log::Info("Application Created!");

		Window::OnWindowClose += RB_BIND_FNC(onWindowClose);
	}

	Application::~Application()
	{
		m_LayerStack.Clear();
		Renderer::Destruct();

		Log::Info("Application closing...");
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Time::OnUpdate();
			m_Window->OnUpdate();
			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			if (Time::GetFixedDeltaTime() > 0.0f)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnFixedUpdate();
				}
			}
		}
	}
	bool Application::onWindowClose()
	{
		m_Running = false;
		return false;
	}
}