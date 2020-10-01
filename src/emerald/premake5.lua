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
		"./**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"IMGUI_IMPL_OPENGL_LOADER_GLAD",
		"STB_IMAGE_IMPLEMENTATION"
	}

	includedirs
	{
		"./",
		"%{IncludeDir.spdlog}",
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

		enablewarnings { "4" }

	filter "system:linux"
		links
		{
			"GL",
			"GLU",
			"X11",
			"dl",
			"pthread"
		}

		enablewarnings { "pedantic" }

	filter "system:macosx"
		links
		{
			"GL",
			"pthread"
		}

		enablewarnings { "pedantic" }

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
