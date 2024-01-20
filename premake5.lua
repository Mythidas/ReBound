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
    include "RBEngine/vendor/imguizmo"
    include "RBEngine/vendor/yaml-cpp"
group ""

group "Core"
    include "RBEngine"
    include "RBEditor"
    include "RBEditorUI"
group ""

group "Misc"
    include "Sandbox"
group ""