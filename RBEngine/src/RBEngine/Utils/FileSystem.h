#pragma once

#include <filesystem>

namespace RB
{
	namespace FS = std::filesystem;

	class FileSystem
	{
	public:
		FileSystem() = default;
		FileSystem(FS::path path) : m_InternalPath(path) {}
		FileSystem(const char* path) : m_InternalPath(path) {}
		FileSystem(const std::string& path) : m_InternalPath(path) {}

		void Write(const std::string& str);

		std::string StreamString();
		std::vector<unsigned char> StreamBuffer();
		std::vector<char> StreamSignedBuffer();

		std::string ToString() const { return m_InternalPath.string(); }

		static FileSystem GetCurrentPath() { return FS::current_path(); }

	private:
		std::ifstream getStream(bool binary = false);

	private:
		FS::path m_InternalPath;
	};
}