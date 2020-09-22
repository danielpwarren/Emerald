project "Emerald"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "core/empch.h"
	pchsource "core/empch.cpp"

	files
	{
		"./**.h",
		"./**.cpp",
		"../external/glm/glm/**.hpp",
		"../external/glm/glm/**.inl",
		"../external/stb/**.hpp",
		"../external/stb/**.h",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"STB_IMAGE_IMPLEMENTATION"
	}

	includedirs
	{
		"./",
		"../external/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		links
		{
			"opengl32.lib"
		}

		defines
		{
			"EM_PLATFORM_WINDOWS"
		}
	
	filter "system:linux"
		links
		{
			"GL",
			"GLU",
			"X11",
			"dl",
			"pthread"
		}
	
		defines
		{
			"EM_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "EM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EM_DIST"
		runtime "Release"
		optimize "on"
