#pragma once

#include "EntityRegistry.h"

namespace RB
{
	class Scene
	{
	public:
		EntityRegistry& GetRegistry() { return m_Registry; }
		
	private:
		EntityRegistry m_Registry;
	};
}