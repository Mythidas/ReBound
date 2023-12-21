#include "rbpch.h"
#include "Renderer.h"
#include "RenderBuffer.h"
#include "GraphicsPipline.h"
#include "RenderCommands.h"
#include "RBEngine/Core/Application.h"

namespace RB
{
	RenderAPI Renderer::s_API = RenderAPI::OpenGL;

	namespace Render
	{
		static const int MaxQuads = 100;
		static const int MaxVertices = MaxQuads * 4;
		static const int MaxIndices = MaxQuads * 6;

		struct Vertex
		{
			Vector3 Position;
			Vector3 Color;
		};

		struct Data
		{
			Ref<GraphicsPipeline> QuadPipeline;
			Ref<RenderBuffer> QuadBuffer;
			Vertex* QuadStagingBuffer{ nullptr };
			Vertex* QuadBufferPtr{ nullptr };
			uint32_t QuadIndexCount{ 0 };

			Ref<Framebuffer> SwapBuffer;

			struct CameraBuffer
			{
				Matrix4 View{ 1.0f };
				Matrix4 Projection{ 1.0f };
			} Camera;

			Ref<RenderBuffer> CameraUniform;
		};
	}

	static Render::Data s_Data;

	void Renderer::Construct()
	{
		s_Data.QuadBuffer = RenderBuffer::Builder()
			.setSize(sizeof(Render::Vertex) * Render::MaxVertices)
			.setUsage(BufferUsage::Vertex)
			.setRate(BufferRate::Dynamic)
			.Build();

		s_Data.QuadStagingBuffer = new Render::Vertex[Render::MaxVertices];

		uint32_t indices[Render::MaxIndices]{};
		uint32_t offset = 0;
		for (size_t i = 0; i < Render::MaxIndices; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		Ref<RenderBuffer> indexBuffer = RenderBuffer::Builder()
			.setSize(sizeof(indices))
			.setUsage(BufferUsage::Index)
			.setRate(BufferRate::Static)
			.Build();

		indexBuffer->SetData(indices, sizeof(indices), 0);

		s_Data.CameraUniform = RenderBuffer::Builder()
			.setBinding(0)
			.setRate(BufferRate::Dynamic)
			.setSize(sizeof(Render::Data::CameraBuffer))
			.setUsage(BufferUsage::Uniform)
			.Build();

		s_Data.QuadPipeline = GraphicsPipeline::Builder()
			.setVertPath("../../Assets/Shaders/QuadShader.vert")
			.setFragPath("../../Assets/Shaders/QuadShader.frag")
			.setVertexBuffer(s_Data.QuadBuffer)
			.setIndexBuffer(indexBuffer)
			.setRenderBuffers({ s_Data.CameraUniform })
			.setAttributes({ VertexAttribute::Float3, VertexAttribute::Float3 })
			.Build();

		s_Data.SwapBuffer = Framebuffer::Builder()
			.setSize({ Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight() })
			.Build();
	}

	void Renderer::Destruct()
	{
		delete[] s_Data.QuadStagingBuffer;
	}

	void Renderer::BeginFrame(const CameraComponent& camera, const TransformComponent& transform)
	{
		TransformComponent transformCopy(transform);
		transformCopy.Position.y *= -1;
		transformCopy.Position.z *= -1;

		s_Data.Camera.View = transformCopy.GetInverseMatrix();
		s_Data.Camera.Projection = camera.Projection;
		s_Data.CameraUniform->SetData(&s_Data.Camera, sizeof(Render::Data::CameraBuffer), 0);

		s_Data.QuadBufferPtr = s_Data.QuadStagingBuffer;
		s_Data.QuadIndexCount = 0;

		s_Data.SwapBuffer->Bind();
		RenderCommands::ClearColor(camera.ClearColor);
	}

	void Renderer::EndFrame()
	{
		size_t size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadStagingBuffer;
		s_Data.QuadBuffer->SetData(s_Data.QuadStagingBuffer, size, 0);

		s_Data.QuadPipeline->Draw(s_Data.QuadIndexCount);

		s_Data.SwapBuffer->Unbind();
	}

	void Renderer::DrawQuad(const Vector3& position)
	{
		s_Data.QuadBufferPtr->Position = Vector3(position.x - 0.5f, position.y - 0.5f, position.z);
		s_Data.QuadBufferPtr->Color = Vector3(1.0f);
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = Vector3(position.x + 0.5f, position.y - 0.5f, position.z);
		s_Data.QuadBufferPtr->Color = Vector3(1.0f);
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = Vector3(position.x + 0.5f, position.y + 0.5f, position.z);
		s_Data.QuadBufferPtr->Color = Vector3(1.0f);
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = Vector3(position.x - 0.5f, position.y + 0.5f, position.z);
		s_Data.QuadBufferPtr->Color = Vector3(1.0f);
		s_Data.QuadBufferPtr++;

		s_Data.QuadIndexCount += 6;
	}

	void Renderer::Resize(const UVector2& size)
	{
		s_Data.SwapBuffer->Resize(size);
		RenderCommands::Resize(size);
	}

	Ref<Framebuffer> Renderer::GetFramebuffer()
	{
		return s_Data.SwapBuffer;
	}
}