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
			Ref<RenderBuffer> Build() { return CreateRef<RenderBuffer>(*this); }
		};

		RenderBuffer(const Builder& builder);

		void Bind() const;
		void SetData(void* data, size_t size, uint32_t offset);
		void* MapBufferPtr(BufferAccess access);
		void UnMapBufferPtr();

	private:
		Builder m_Builder;
		uint32_t m_RenderID;
	};
}