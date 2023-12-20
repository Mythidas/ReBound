#pragma once

#include "Registry.h"

namespace RB
{
	class Scene
	{
	public:
		Registry& GetRegistry() { return m_Registry; }
		
	private:
		Registry m_Registry;
	};
}