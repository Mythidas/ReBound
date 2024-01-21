#pragma once

#include "RBEngine/Debug/Result.h"

#include <filesystem>

namespace RB
{
	namespace FS = std::filesystem;

	class Directory
	{
	public:
		Directory() = default;
		Directory(const FS::path& path);
		Directory(const std::string& path);

		Debug::Result CreateDir() const;
		std::vector<FS::path> GetFilesInDir() const;
		std::vector<FS::path> GetDirectoriesInDir() const;

		bool Valid() const { return !m_Path.empty(); }
		bool Exists() const { return FS::exists(m_Path); }
		bool HasFiles() const;
		bool HasDirectories() const;
		std::string Name() const { return m_Path.filename().string(); }
		std::string ToString() const { return m_Path.string(); }

		Directory operator+(const std::string& rhs) const
		{
			return m_Path.string() + rhs;
		}

		bool operator==(const Directory& rhs) const
		{
			return m_Path == rhs.m_Path;
		}

		operator FS::path() const
		{
			return m_Path;
		}

	public:
		static Directory GetDirectoryDialog();

	private:
		FS::path m_Path;
		bool m_Invalid{ true };
	};
}