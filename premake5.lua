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

--startproject "Sandbox"

project "Vitar"
    location "Vitar"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

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
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "VITAR_PLANTFORM_WINDOWS",
            "VITAR_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "IMGUI_API=__declspec(dllexport)",
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\""),
        }

    filter "configurations:Debug"
        defines "VITAR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "VITAR_Release"
        runtime "Release"
        symbols "On"

    filter "configurations:Dist"
        defines "VITAR_Dist"
        runtime "Release"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "VITAR_PLANTFORM_WINDOWS",
            "IMGUI_API=__declspec(dllimport)",
        }

    filter "configurations:Debug"
        defines "VITAR_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "VITAR_Release"
        runtime "Release"
        symbols "On"

    filter "configurations:Dist"
        defines "VITAR_Dist"
        runtime "Release"
        symbols "On"
