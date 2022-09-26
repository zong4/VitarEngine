project "Vitar"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "VitarPCH.h"
    pchsource "src/VitarPCH.cpp"

   files
   {
        "src/**.h",
        "src/**.cpp",
        "vendor/stb_image/**.h",
        "vendor/stb_image/**.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",
   }

   defines
   {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE",
   }

   includedirs
   {
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}"
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
            -- "VITAR_PLANTFORM_WINDOWS",
            -- "VITAR_BUILD_DLL",
            -- "GLFW_INCLUDE_NONE",
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