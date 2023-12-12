#pragma once

namespace RB
{
	enum class RenderAPI
	{
		None,
		OpenGL
	};

	class Renderer
	{
	public:
		static RenderAPI GetAPI() { return s_API; }

	private:
		static RenderAPI s_API;
	};
}