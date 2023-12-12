#pragma once

#ifdef RB_PLAT_WINDOWS

extern RB::Application* RB::CreateApplication();

int main(int argc, char** argv)
{
	auto app = RB::CreateApplication();
	app->Run();
	delete app;
}

#endif