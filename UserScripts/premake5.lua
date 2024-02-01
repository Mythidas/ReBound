include "dependencies.lua"

project "UserScripts"
    kind "SharedLib"
    language "C++"
    cppdialect "C++latest"
    staticruntime "off"

    targetdir ("bin/")
    objdir ("bin-int/")

    files
    {
        "**.h",
        "**.cpp",
    }

    includedirs
    {
        "src",
        "%{wks.location}/RBEngine/src",
        "%{IncludeDir.SPD}",
        "%{IncludeDir.GLM}",
    }

    defines
    {
        "RB_API_EXPORT"
    }

    links
    {
        "RBEngine"
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