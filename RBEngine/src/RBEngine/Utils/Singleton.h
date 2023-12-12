#pragma once

#include "RBEngine/Core/Defines.h"
#include "RBEngine/Debug/Assert.h"

namespace RB
{
	template <typename T>
	class Singleton
	{
	public:
		Singleton()
		{
			RB_ASSERT(!s_Instance, "{0} already exists!", GetTypeName<T>());
			s_Instance = static_cast<T*>(this);
		}

		static T& Get() { return *s_Instance; }

	private:
		static T* s_Instance;
	};

	template <typename T>
	inline T* Singleton<T>::s_Instance = nullptr;
}