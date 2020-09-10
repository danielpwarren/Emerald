project "Sandbox"
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
	}

	links
	{
		"Emerald"
	}

	filter "system:windows"
		systemversion "latest"

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