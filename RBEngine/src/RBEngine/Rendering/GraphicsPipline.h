#pragma once

#include "RBEngine/Core/Defines.h"
#include "RenderBuffer.h"

namespace RB
{
	enum class VertexAttribute
	{
		Float,
		Float2,
		Float3,
		Float4
	};

	class GraphicsPipeline
	{
	public:
		struct Builder
		{
			std::string VertPath;
			std::string FragPath;
			Ref<RenderBuffer> pVertexBuffer;
			Ref<RenderBuffer> pIndexBuffer;
			std::vector<VertexAttribute> Attributes;

			Builder& setVertPath(const std::string& path) { VertPath = path; return *this; }
			Builder& setFragPath(const std::string& path) { FragPath = path; return *this; }
			Builder& setVertexBuffer(const Ref<RenderBuffer>& buffer) { pVertexBuffer = buffer; return *this; }
			Builder& setIndexBuffer(const Ref<RenderBuffer>& buffer) { pIndexBuffer = buffer; return *this; }
			Builder& setAttributes(const std::vector<VertexAttribute>& attributes) { Attributes = attributes; return *this; }
			Ref<GraphicsPipeline> Build() { return CreateRef<GraphicsPipeline>(*this); }
		};

		GraphicsPipeline(const Builder& builder);

		void Draw(uint32_t count) const;

	private:
		Builder m_Builder;
		uint32_t m_RenderID;
		uint32_t m_VertexID;
	};
}