#include "rbpch.h"
#include "Project.h"
#include "Application.h"

#include <yaml-cpp/yaml.h>

namespace RB
{
	Directory Project::s_Dir{};
	std::string Project::s_Name{ "New Project" };
	uint32_t Project::s_Version{ Bit::U32_4x8(0, 0, 1, 0) };

	Debug::Result Project::NewProject(const Directory& path)
	{
		Timer timer;

		if (!path.Exists())
		{
			return  { Debug::ResultCode::Invalid, "Invalid project directory!" };
		}

		s_Dir = path;
		SaveProject();

		Debug::Log::Info("Project file created...");

		// Create the assets directory
		if (auto result = GetAssestsDir().CreateDir(); result & Debug::ResultCode::Success)
		{
			Debug::Log::Info("Asset Directory created...");
		}

		Debug::Log::Info("Project creation completed. [{0}] ({1})", timer.ElapsedMill(), path.ToString());
		return Debug::ResultCode::Success;
	}

	Debug::Result Project::LoadProject(const File& path)
	{
		if (!path.Exists() || path.Extension() != ".rebound")
			return Debug::ResultCode::Invalid;

		YAML::Node in = YAML::Load(path.ReadString());
		if (!in["Project"])
			return Debug::ResultCode::Invalid;

		if (in["Engine Version"].as<uint32_t>() != Application::VERSION)
		{
			std::stringstream ss;
			ss << "Project is using a different Engine Version! Current (" << Application::VERSION << "), Project (" << in["Engine Version"].as<uint32_t>() << ")";
			return { Debug::ResultCode::Error, ss.str() };
		}

		s_Dir = path.GetDirectory();
		s_Version = in["Project Version"].as<uint32_t>();

		return Debug::ResultCode::Success;
	}

	Debug::Result Project::SaveProject()
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Project" << YAML::Value << s_Name;
		out << YAML::Key << "Engine Version" << YAML::Value << Application::VERSION;
		out << YAML::Key << "Project Version" << YAML::Key << s_Version;
		out << YAML::EndMap;

		File(s_Dir + "/project.rebound").Write(out.c_str());

		return Debug::ResultCode::Success;
	}
}