#include "RBEngine.h"
#include "RBEngine/Core/EntryPoint.h"

class SimpleLayer : public RB::Layer
{
public:
	virtual void OnAttach() override
	{
		RB::Log::Info("SimpleLayer Attached!");
	}

	RB::Vector3 Pos{ 0 };

	virtual void OnUpdate() override
	{
		RB::Renderer::BeginFrame();
		RB::Renderer::DrawQuad(Pos);
		RB::Renderer::EndFrame();
	}
};

class SandboxApp : public RB::Application
{
public:
	SandboxApp()
	{
		PushLayer(new SimpleLayer());
	}
};

RB::Application* RB::CreateApplication()
{
	return new SandboxApp();
}