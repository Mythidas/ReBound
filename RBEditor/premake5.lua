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
        "%{wks.location}/RBEngine/src",
        "%{IncludeDir.SPD}",
        "%{IncludeDir.GLM}",
    }

    links
    {
        "RBEngine"
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