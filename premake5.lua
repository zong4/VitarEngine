include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Vitar"
    architecture "x64"
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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Vitar/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Vitar/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Vitar/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Vitar/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Vitar/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Vitar/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Vitar/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Vitar/vendor/ImGuizmo"

group "Dependencies"
    include "vendor/premake"
	include "Vitar/vendor/GLFW"
	include "Vitar/vendor/Glad"
	include "Vitar/vendor/imgui"
    include "Vitar/vendor/yaml-cpp"

group ""

include "Vitar"
include "Sandbox"
include "VitarEditor"