#pragma once

#include "RBEngine/Debug/Result.h"
#include "RBEngine/Utils/File.h"
#include "RBEngine/Utils/Directory.h"
#include "RBEngine/Utils/Singleton.h"
#include "RBEngine/Utils/Bit.h"

namespace RB
{
	class Project
	{
	public:
		static Debug::Result NewProject(const Directory& path);
		static Debug::Result LoadProject(const File& path);
		static Debug::Result SaveProject();

		static const uint32_t GetProjectVersion() { return s_Version; }
		static const Directory GetProjectDir() { return s_Dir; }
		static const Directory GetAssestsDir() { return s_Dir + "/Assets"; }

	private:
		static Directory s_Dir;
		static std::string s_Name;
		static uint32_t s_Version;
	};
}