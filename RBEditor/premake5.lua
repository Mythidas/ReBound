include "dependencies.lua"

project "RBEditor"
    location "src"
    kind "ConsoleApp"
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

    includedirs
    {
        "src",
        "%{wks.location}/RBEngine/src",
        "%{wks.location}/RBEditorUI/src",
        "%{IncludeDir.SPD}",
        "%{IncludeDir.STB}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.IMGUI}",
        "%{IncludeDir.IMGUIZMO}",
        "%{IncludeDir.YAML_CPP}"
    }

    links
    {
        "RBEngine",
        "RBEditorUI",
        "ImGui",
        "ImGuizmo",
        "yaml-cpp"
    }

    defines
    {
        "YAML_CPP_STATIC_DEFINE"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "RB_PLAT_WINDOWS",
        }

    filter "configurations:Debug"
        defines "RB_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RB_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "RB_DIST"
        optimize "On"
        runtime "Release"