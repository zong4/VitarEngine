include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Vitar"
    architecture "x86_64"
    startproject "VitarEditor"
    configurations { "Debug", "Release", "Dist" }

    solution_items
	{
		".editorconfig",
	}

    flags
	{
		"MultiProcessorCompile",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "vendor/premake"
	include "Vitar/vendor/Box2D"
	include "Vitar/vendor/GLFW"
	include "Vitar/vendor/Glad"
	include "Vitar/vendor/imgui"
    include "Vitar/vendor/yaml-cpp"
group ""

group "Core"
	include "Vitar"
	include "Vitar-ScriptCore"
group ""

group "Tools"
	include "VitarEditor"
group ""

-- group "Misc"
-- 	include "Sandbox"
-- group ""