-- premake5.lua
workspace "Vitar"
    architecture "x64"
    startproject "Sandbox"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Vitar/vendor/GLFW/include"
IncludeDir["Glad"] = "Vitar/vendor/Glad/include"
IncludeDir["ImGui"] = "Vitar/vendor/imgui"
IncludeDir["glm"] = "Vitar/vendor/glm"

include "Vitar/vendor/GLFW"
include "Vitar/vendor/Glad"
include "Vitar/vendor/imgui"

project "Vitar"
    location "Vitar"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "VitarPCH.h"
    pchsource "Vitar/src/VitarPCH.cpp"

   files
   {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
   }

   defines
   {
        "_CRT_SECURE_NO_WARNINGS",
   }

   includedirs
   {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
   }

   links
   {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
   }

   filter "system:windows"
        systemversion "latest"

        defines
        {
            "VITAR_PLANTFORM_WINDOWS",
            "VITAR_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "IMGUI_API=__declspec(dllexport)",
        }

    filter "configurations:Debug"
        defines "VITAR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "VITAR_Release"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "VITAR_Dist"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
 
    includedirs
    {
        "Vitar/vendor/spdlog/include",
        "Vitar/src",
        "Vitar/vendor",
        "%{IncludeDir.glm}",
    }

    links
    {
        "Vitar",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "VITAR_PLANTFORM_WINDOWS",
            "IMGUI_API=__declspec(dllimport)",
        }

    filter "configurations:Debug"
        defines "VITAR_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "VITAR_Release"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "VITAR_Dist"
        runtime "Release"
        optimize "on"