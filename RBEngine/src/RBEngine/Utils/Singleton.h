#pragma once

#include "RBEngine/Debug/Assert.h"
#include "RBEngine/Reflection/Type.h"

namespace RB
{
	template <typename T>
	class Singleton
	{
	public:
		Singleton()
		{
			RB_ASSERT(!s_Instance, "{0} already exists!", Type<T>().Name());
			s_Instance = static_cast<T*>(this);
		}

		static T& Get() { return *s_Instance; }

	private:
		static T* s_Instance;
	};

	template <typename T>
	inline T* Singleton<T>::s_Instance = nullptr;
}