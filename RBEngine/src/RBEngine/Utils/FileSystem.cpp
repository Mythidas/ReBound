#include "rbpch.h"
#include "FileSystem.h"

namespace RB
{
	void FileSystem::Write(const std::string& str)
	{
		std::ofstream fout(m_InternalPath);
		fout << str.c_str();
	}

	std::string FileSystem::StreamString()
	{
		std::ifstream stream = getStream();

		std::stringstream buffer;
		buffer << stream.rdbuf();
		stream.close();
		return buffer.str();
	}

	std::vector<unsigned char> FileSystem::StreamBuffer()
	{
		std::ifstream stream = getStream(true);

		std::vector<unsigned char> buffer;
		unsigned char value = 0;
		while (stream.read(reinterpret_cast<char*>(&value), sizeof(value)))
		{
			buffer.push_back(value);
		}

		stream.close();
		return buffer;
	}

	std::vector<char> FileSystem::StreamSignedBuffer()
	{
		std::ifstream stream = getStream(true);

		std::vector<char> buffer;
		char value = 0;
		while (stream.read(reinterpret_cast<char*>(&value), sizeof(value)))
		{
			buffer.push_back(value);
		}

		stream.close();
		return buffer;
	}

	std::ifstream FileSystem::getStream(bool binary)
	{
		if (binary)
		{
			std::ifstream stream(m_InternalPath.c_str(), std::ios::binary);
			if (!stream.is_open())
			{
				Debug::Log::Warn("Failed to open file {0}", m_InternalPath.string());
			}

			return stream;
		}
		else
		{
			std::ifstream stream(m_InternalPath.c_str());
			if (!stream.is_open())
			{
				Debug::Log::Warn("Failed to open file {0}", m_InternalPath.string());
			}

			return stream;
		}
	}
}