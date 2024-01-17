include "dependencies.lua"

project "RBEngine"
    location "src"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rbpch.h"
    pchsource "src/rbpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
        "YAML_CPP_STATIC_DEFINE"
	}

    includedirs
    {
        "src",
        "%{IncludeDir.SPD}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.STB}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.IMGUI}",
        "%{IncludeDir.IMGUIZMO}",
        "%{IncludeDir.YAML_CPP}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "ImGuizmo",
        "yaml-cpp",
        "OpenGL32.lib"
    }

    flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "RB_PLAT_WINDOWS",
        }

    filter "configurations:Debug"
        defines
        {
            "RB_DEBUG",
            "RB_ASSERTS_ENABLED"
        }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines "RB_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "RB_DIST"
        optimize "On"
        runtime "Release"