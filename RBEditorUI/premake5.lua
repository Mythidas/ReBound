include "dependencies.lua"

project "RBEditorUI"
    location "src"
    kind "StaticLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
    {
        "src",
        "%{wks.location}/RBEngine/src",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.IMGUI}",
        "%{IncludeDir.IMGUIZMO}"
    }

    links
    {
        "ImGui",
        "ImGuizmo",
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