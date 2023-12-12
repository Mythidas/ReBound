#include "RBEngine.h"
#include "RBEngine/Core/EntryPoint.h"

class SimpleLayer : public RB::Layer
{
public:
	virtual void OnAttach() override
	{
		RB::Log::Info("SimpleLayer Attached!");
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