#pragma once

#include "RBEngine/Core/Defines.h"

namespace RB
{
	enum class BufferUsage
	{
		Vertex,
		Index,
		Uniform,
		ShaderStorage
	};

	enum class BufferRate
	{
		Static,
		Dynamic
	};

	enum class BufferAccess
	{
		ReadOnly,
		WriteOnly,
		ReadWrite
	};

	class RenderBuffer
	{
	public:
		struct Builder
		{
			size_t Size;
			uint32_t Binding;
			BufferUsage Usage;
			BufferRate Rate;

			Builder& setSize(size_t size) { Size = size; return *this; }
			Builder& setBinding(uint32_t binding) { Binding = binding; return *this; }
			Builder& setUsage(BufferUsage usage) { Usage = usage; return *this; }
			Builder& setRate(BufferRate rate) { Rate = rate; return *this; }
			Ref<RenderBuffer> Build() { return Create(*this); }
		};

		virtual void Bind() const = 0;
		virtual void SetData(void* data, size_t size, uint32_t offset) = 0;
		virtual void* MapBufferPtr(BufferAccess access) = 0;
		virtual void UnMapBufferPtr() = 0;

		static Ref<RenderBuffer> Create(const Builder& builder);
	};
}