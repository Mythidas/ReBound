#include "rbpch.h"
#include "GraphicsPipline.h"
#include "RBEngine/Utils/FileSystem.h"

#include <glad/glad.h>

namespace RB
{
	namespace Utils
	{
		Result LogShaderError(uint32_t shader)
		{
			int success;
			char infoLog[512];

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, nullptr, infoLog);
				Log::Error("Shader Compile Error: {0}", infoLog);
				return Result::Error;
			}

			return Result::Success;
		}

		Result LogProgramError(uint32_t program)
		{
			int success;
			char infoLog[512];

			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(program, 512, nullptr, infoLog);
				Log::Error("Program Link Error: {0}", infoLog);
				return Result::Error;
			}

			return Result::Success;
		}

		int GetAttributeSize(VertexAttribute attrib)
		{
			switch (attrib)
			{
			case VertexAttribute::Float: return 4 * 1;
			case VertexAttribute::Float2: return 4 * 2;
			case VertexAttribute::Float3: return 4 * 3;
			case VertexAttribute::Float4: return 4 * 4;
			default: return 4;
			}
		}

		int GetAttributeCount(VertexAttribute attrib)
		{
			switch (attrib)
			{
			case VertexAttribute::Float: return 1;
			case VertexAttribute::Float2: return 2;
			case VertexAttribute::Float3: return 3;
			case VertexAttribute::Float4: return 4;
			default: return 1;
			}
		}

		GLenum GetAttributeType(VertexAttribute attrib)
		{
			switch (attrib)
			{
			case VertexAttribute::Float: return GL_FLOAT;
			case VertexAttribute::Float2: return GL_FLOAT;
			case VertexAttribute::Float3: return GL_FLOAT;
			case VertexAttribute::Float4: return GL_FLOAT;
			default: return GL_FLOAT;
			}
		}
	}

	GraphicsPipeline::GraphicsPipeline(const Builder& builder)
		: m_Builder(builder), m_RenderID(0), m_VertexID(0)
	{
		std::string vertSrc = FileSystem(builder.VertPath).StreamString();
		std::string fragSrc = FileSystem(builder.FragPath).StreamString();

		const char* vertCode = vertSrc.c_str();
		const char* fragCode = fragSrc.c_str();

		uint32_t vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertCode, nullptr);
		glCompileShader(vertShader);

		if (Utils::LogShaderError(vertShader) != Result::Success)
		{
			Log::Error("Failed to Create Shader: {0}", builder.VertPath);
			return;
		}

		uint32_t fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragCode, nullptr);
		glCompileShader(fragShader);

		if (Utils::LogShaderError(fragShader) != Result::Success)
		{
			Log::Error("Failed to Create Shader: {0}", builder.FragPath);
			return;
		}

		m_RenderID = glCreateProgram();
		glAttachShader(m_RenderID, vertShader);
		glAttachShader(m_RenderID, fragShader);
		glLinkProgram(m_RenderID);

		if (Utils::LogProgramError(m_RenderID) != Result::Success)
		{
			Log::Error("Failed to Create Program ID {0}: Link Error", m_RenderID);
			return;
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		glGenVertexArrays(1, &m_VertexID);
		glBindVertexArray(m_VertexID);

		m_Builder.pVertexBuffer->Bind();
		m_Builder.pIndexBuffer->Bind();

		size_t stride = 0;
		for (auto& attrib : m_Builder.Attributes)
		{
			stride += Utils::GetAttributeSize(attrib);
		}

		size_t offset = 0;
		for (size_t i = 0; i < m_Builder.Attributes.size(); i++)
		{
			glEnableVertexArrayAttrib(m_VertexID, i);
			glVertexAttribPointer(i, Utils::GetAttributeCount(m_Builder.Attributes[i]), Utils::GetAttributeType(m_Builder.Attributes[i]), GL_FALSE, stride, (void*)offset);
			offset += Utils::GetAttributeSize(m_Builder.Attributes[i]);
		}
	}

	void GraphicsPipeline::Draw(uint32_t count) const
	{
		glBindVertexArray(m_VertexID);
		
		if (m_Builder.pIndexBuffer)
		{
			m_Builder.pIndexBuffer->Bind();
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	}
}