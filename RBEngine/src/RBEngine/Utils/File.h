#pragma once

#include <filesystem>

namespace RB
{
	namespace FS = std::filesystem;

	enum class DialogFilter
	{
		Project,
		Scene,
		Text,
		JPG,
		PNG
	};

	class File
	{
	public:
		File() = default;
		File(FS::path path);
		File(const std::string& path);
		File(const char* path);

		void Write(const char* data) const;
		void Write(const std::string& data) const;

		std::string ReadString() const;
		std::vector<unsigned char> ReadBuffer() const;
		std::vector<char> ReadSignedBuffer() const;

		bool Valid() const { return m_Invalid; }
		bool Exists() const { return FS::exists(m_Path); }
		std::string Extension() const { return m_Path.extension().string(); }
		std::string Name() const { return m_Path.filename().string(); }
		std::string ToString() const { return m_Path.string(); }
		FS::path GetDirectory() const { return m_Path.parent_path(); }

		operator FS::path() const
		{
			return m_Path;
		}

	public:
		static File GetFileDialog(const std::vector<DialogFilter>& filter);

	private:
		std::ifstream _GetStream(bool binary = false) const;

	private:
		FS::path m_Path;
		bool m_Invalid{ true };
	};
}