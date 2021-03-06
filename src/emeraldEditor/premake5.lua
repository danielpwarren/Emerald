project "EmeraldEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"./**.h",
		"./**.cpp"
	}

	includedirs
	{
		"%{wks.location}/src/external/spdlog/include",
		"%{wks.location}/src/emerald",
		"%{wks.location}/src/external",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Emerald"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"GL",
			"GLU",
			"X11",
			"dl",
			"pthread"
		}

	filter "system:macosx"
		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"pthread"
		}
        
        linkoptions { "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation" }

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
