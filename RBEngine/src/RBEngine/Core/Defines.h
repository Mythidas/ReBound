#pragma once

#include <memory>
#include <functional>
#include <string>

#define RB_BIND_FNC(fn)  [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace RB
{
	// Scope for unique pointers
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename... Args>
	Scope<T> CreateScope(Args ...args)
	{
		return std::make_unique<T>(args...);
	}

	// Reference for shared pointers
	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename ...Args>
	Ref<T> CreateRef(Args... args)
	{
		return std::make_shared<T>(args...);
	}

	// Weak reference for weak pointers
	template <typename T>
	using WeakRef = std::weak_ptr<T>;

	// Type Traverse
	template <typename T>
	std::string GetTypeName()
	{
		typedef typename std::remove_reference<T>::type TR;
		return typeid(TR).name();
	}
}