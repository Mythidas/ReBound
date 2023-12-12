include "dependencies.lua"

workspace "ReBound"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "RBEngine/vendor/GLFW"
    include "RBEngine/vendor/glad"
    include "RBEngine/vendor/imgui"
group ""

group "Core"
    include "RBEngine"
group ""

group "Misc"
    include "Sandbox"
group ""