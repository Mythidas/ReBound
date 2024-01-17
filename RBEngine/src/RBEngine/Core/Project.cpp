#include "rbpch.h"
#include "Project.h"
#include "Application.h"

#include <yaml-cpp/yaml.h>

namespace RB
{
	Debug::Result Project::NewProject(const Directory& path)
	{
		Timer timer;

		if (!path.Exists())
		{
			return  { Debug::ResultCode::Invalid, "Invalid project directory!" };
		}

		Get().m_Dir = path;
		SaveProject();

		Debug::Log::Info("Project file created...");

		// Create the assets directory
		if (auto result = GetAssestsDir().Create(); result & Debug::ResultCode::Success)
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

		Get().m_Dir = path.GetDirectory();
		Get().m_Version = in["Project Version"].as<uint32_t>();

		return Debug::ResultCode::Success;
	}

	Debug::Result Project::SaveProject()
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Project" << YAML::Value << Get().m_Name;
		out << YAML::Key << "Engine Version" << YAML::Value << Application::VERSION;
		out << YAML::Key << "Project Version" << YAML::Key << Get().m_Version;
		out << YAML::EndMap;

		File(Get().m_Dir + "/project.rebound").Write(out.c_str());

		return Debug::ResultCode::Success;
	}
}