project "VitarEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"%{IncludeDir.ImGuizmo}",
	}

	links
	{
		"Vitar"
	}

	filter "system:windows"
		systemversion "latest"

        -- defines
        -- {
        --     "VITAR_PLANTFORM_WINDOWS",
        -- }

	filter "configurations:Debug"
		defines "VITAR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VITAR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VITAR_DIST"
		runtime "Release"
		optimize "on"