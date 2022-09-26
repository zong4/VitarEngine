project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"assets/shaders/**.**",
        "assets/textures/**.**",
	}

	includedirs
	{
		"%{wks.location}/Vitar/vendor/spdlog/include",
		"%{wks.location}/Vitar/src",
		"%{wks.location}/Vitar/vendor",
        "%{wks.location}/Vitar/vendor/Glad/include",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
	}

	links
	{
		"Vitar"
	}

	filter "system:windows"
		systemversion "latest"

        defines
        {
            "VITAR_PLANTFORM_WINDOWS",
            -- "IMGUI_API=__declspec(dllimport)",
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