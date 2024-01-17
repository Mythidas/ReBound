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

		Debug::Result Create() const;

		bool Valid() const { return !m_Path.empty(); }
		bool Exists() const { return FS::exists(m_Path); }
		std::string ToString() const { return m_Path.string(); }

		Directory operator+(const std::string& rhs) const
		{
			return m_Path.string() + rhs;
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