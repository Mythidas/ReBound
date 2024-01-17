#pragma once

#include "RBEngine/Debug/Result.h"
#include "RBEngine/Utils/File.h"
#include "RBEngine/Utils/Directory.h"
#include "RBEngine/Utils/Singleton.h"
#include "RBEngine/Utils/Bit.h"

namespace RB
{
	class Project : public Singleton<Project>
	{
	public:
		static Debug::Result NewProject(const Directory& path);
		static Debug::Result LoadProject(const File& path);
		static Debug::Result SaveProject();

		static const uint32_t GetProjectVersion() { return Get().m_Version; }
		static const Directory GetAssestsDir() { return Get().m_Dir + "/Assets"; }

	private:
		Directory m_Dir{};
		std::string m_Name{ "New Project" };
		uint32_t m_Version{ Bit::U32_4x8(0, 0, 1, 0) };

	};
}