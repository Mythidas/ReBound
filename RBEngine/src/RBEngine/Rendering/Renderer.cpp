#include "rbpch.h"
#include "Renderer.h"
#include "RenderBuffer.h"
#include "GraphicsPipline.h"
#include "RenderCommands.h"
#include "RBEngine/Core/Application.h"

#include "glm/gtc/matrix_transform.hpp"

namespace RB
{
	RenderAPI Renderer::s_API = RenderAPI::OpenGL;

	namespace Render
	{
		static const int MaxQuads = 100;
		static const int MaxVertices = MaxQuads * 4;
		static const int MaxIndices = MaxQuads * 6;
		static const int MaxTextureSlots = 32;

		struct Vertex
		{
			Vector3 Position;
			Vector3 Color;
			Vector2 TexCoord;
			float TexIndex;
		};

		struct Data
		{
			Ref<GraphicsPipeline> Pipeline;
			Ref<RenderBuffer> Buffer;
			Vertex* StagingBuffer{ nullptr };
			Vertex* StagingBufferPtr{ nullptr };
			uint32_t IndexCount{ 0 };
			uint32_t TextureSlotIndex{ 1 };
			Ref<Image> TextureSlots[MaxTextureSlots];

			Vector4 VertexPositions[4]{};
			Vector2 TexturePositions[4]{};

			Ref<Framebuffer> SwapBuffer;

			struct CameraBuffer
			{
				Matrix4 View{ 1.0f };
				Matrix4 Projection{ 1.0f };
			} Camera;

			Ref<RenderBuffer> CameraUniform;
		};
	}

	static Render::Data s_QuadData;

	void Renderer::_Construct()
	{
		s_QuadData.Buffer = RenderBuffer::Builder()
			.setSize(sizeof(Render::Vertex) * Render::MaxVertices)
			.setUsage(BufferUsage::Vertex)
			.setRate(BufferRate::Dynamic)
			.Build();

		s_QuadData.StagingBuffer = new Render::Vertex[Render::MaxVertices];

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

		s_QuadData.VertexPositions[0] = { 0.5f, 0.5f, 0.0f, 1.0f };
		s_QuadData.VertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_QuadData.VertexPositions[2] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_QuadData.VertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

		s_QuadData.TexturePositions[0] = { 1.0f, 1.0f };
		s_QuadData.TexturePositions[1] = { 1.0f, 0.0f };
		s_QuadData.TexturePositions[2] = { 0.0f, 0.0f };
		s_QuadData.TexturePositions[3] = { 0.0f, 1.0f };

		uint32_t whiteTextureData = 0xFFFFFFFF;
		Ref<Image> whiteTex = Image::Builder()
			.setFormat(ImageFormat::RGBA8)
			.setSize({ 1, 1, 1 })
			.setType(ImageType::e2D)
			.Build();

		whiteTex->SetData(&whiteTextureData, sizeof(uint32_t));
		s_QuadData.TextureSlots[0] = whiteTex;

		s_QuadData.CameraUniform = RenderBuffer::Builder()
			.setBinding(0)
			.setRate(BufferRate::Dynamic)
			.setSize(sizeof(Render::Data::CameraBuffer))
			.setUsage(BufferUsage::Uniform)
			.Build();

		s_QuadData.Pipeline = GraphicsPipeline::Builder()
			.setVertPath("../Assets/Shaders/QuadShader.vert")
			.setFragPath("../Assets/Shaders/QuadShader.frag")
			.setVertexBuffer(s_QuadData.Buffer)
			.setIndexBuffer(indexBuffer)  
			.setRenderBuffers({ s_QuadData.CameraUniform })
			.setAttributes({ VertexAttribute::Float3, VertexAttribute::Float3, VertexAttribute::Float2, VertexAttribute::Float })
			.Build();

		s_QuadData.SwapBuffer = Framebuffer::Builder()
			.setSize({ Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight() })
			.Build();
	}

	void Renderer::_Destruct()
	{
		delete[] s_QuadData.StagingBuffer;
	}

	void Renderer::BeginFrame(const Camera& camera, const Transform& transform)
	{
		Transform transformCopy(transform);
		transformCopy.Position.y *= -1;
		transformCopy.Position.z *= -1;

		s_QuadData.Camera.View = transformCopy.GetInverseMatrix();
		s_QuadData.Camera.Projection = camera.Projection;
		s_QuadData.CameraUniform->SetData(&s_QuadData.Camera, sizeof(Render::Data::CameraBuffer), 0);

		s_QuadData.SwapBuffer->Bind();
		RenderCommands::ClearColor(camera.ClearColor);

		_BeginBatch();
	}

	void Renderer::EndFrame()
	{
		_EndBatch();
		s_QuadData.SwapBuffer->Unbind();
	}

	void Renderer::DrawQuad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Vector3& color)
	{
		Matrix4 transform = glm::translate(Matrix4(1.0f), glm::vec3(position))
			* glm::scale(Matrix4(1.0f), glm::vec3(scale))
			* glm::rotate(Matrix4(1.0f), glm::radians(rotation.x), glm::vec3(Vector3(1.0f, 0.0f, 0.0f)))
			* glm::rotate(Matrix4(1.0f), glm::radians(rotation.y), glm::vec3(Vector3(0.0f, 1.0f, 0.0f)))
			* glm::rotate(Matrix4(1.0f), glm::radians(rotation.z), glm::vec3(Vector3(0.0f, 0.0f, 1.0f)));

		DrawQuad(transform, color, 0.0f);
	}

	void Renderer::DrawQuad(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Vector3& color, Ref<Image> texture)
	{
		Matrix4 transform = glm::translate(Matrix4(1.0f), glm::vec3(position))
			* glm::scale(Matrix4(1.0f), glm::vec3(scale))
			* glm::rotate(Matrix4(1.0f), glm::radians(rotation.x), glm::vec3(Vector3(1.0f, 0.0f, 0.0f)))
			* glm::rotate(Matrix4(1.0f), glm::radians(rotation.y), glm::vec3(Vector3(0.0f, 1.0f, 0.0f)))
			* glm::rotate(Matrix4(1.0f), glm::radians(rotation.z), glm::vec3(Vector3(0.0f, 0.0f, 1.0f)));

		float texIndex = _GetTextureIndex(texture);
		DrawQuad(transform, color, texIndex);
	}

	void Renderer::DrawQuad(const Matrix4& transform, const Vector3& color, float texIndex)
	{
		_CheckBatch();

		for (size_t i = 0; i < 4; i++)
		{
			s_QuadData.StagingBufferPtr->Position = Vector3(transform * (glm::vec4)s_QuadData.VertexPositions[i]);
			s_QuadData.StagingBufferPtr->Color = color;
			s_QuadData.StagingBufferPtr->TexCoord = s_QuadData.TexturePositions[i];
			s_QuadData.StagingBufferPtr->TexIndex = texIndex;
			s_QuadData.StagingBufferPtr++;
		}

		s_QuadData.IndexCount += 6;
	}

	void Renderer::DrawQuad(const Matrix4& transform, const Vector3& color, Vector2 texCoords[4], float texIndex)
	{
		_CheckBatch();

		for (size_t i = 0; i < 4; i++)
		{
			s_QuadData.StagingBufferPtr->Position = Vector3(transform * (glm::vec4)s_QuadData.VertexPositions[i]);
			s_QuadData.StagingBufferPtr->Color = color;
			s_QuadData.StagingBufferPtr->TexCoord = texCoords[i];
			s_QuadData.StagingBufferPtr->TexIndex = texIndex;
			s_QuadData.StagingBufferPtr++;
		}

		s_QuadData.IndexCount += 6;
	}

	void Renderer::Resize(const UVector2& size)
	{
		s_QuadData.SwapBuffer->Resize(size);
		RenderCommands::Resize(size);
	}

	Ref<Framebuffer> Renderer::GetFramebuffer()
	{
		return s_QuadData.SwapBuffer;
	}

	void Renderer::_CheckBatch()
	{
		if (s_QuadData.IndexCount >= Render::MaxIndices || s_QuadData.TextureSlotIndex == Render::MaxTextureSlots)
		{
			_EndBatch();
			_BeginBatch();
		}
	}

	void Renderer::_BeginBatch()
	{
		s_QuadData.StagingBufferPtr = s_QuadData.StagingBuffer;
		s_QuadData.IndexCount = 0;
		s_QuadData.TextureSlotIndex = 1;
	}

	void Renderer::_EndBatch()
	{
		for (uint32_t i = 0; i < s_QuadData.TextureSlotIndex; i++)
		{
			s_QuadData.TextureSlots[i]->Bind(i);
		}

		size_t size = (uint8_t*)s_QuadData.StagingBufferPtr - (uint8_t*)s_QuadData.StagingBuffer;
		s_QuadData.Buffer->SetData(s_QuadData.StagingBuffer, size, 0);

		s_QuadData.Pipeline->Draw(s_QuadData.IndexCount);
	}

	float Renderer::_GetTextureIndex(Ref<Image> texture)
	{
		float texIndex = 0.0f;
		for (uint32_t i = 1; i < s_QuadData.TextureSlotIndex; i++)
		{
			if (*(float*)s_QuadData.TextureSlots[i]->GetRenderID() == *(float*)texture->GetRenderID())
			{
				texIndex = (float)i;
				break;
			}
		}

		if (texIndex == 0.0f)
		{
			texIndex = (float)s_QuadData.TextureSlotIndex;
			s_QuadData.TextureSlots[(size_t)texIndex] = texture;
			s_QuadData.TextureSlotIndex++;
		}

		return texIndex;
	}
}