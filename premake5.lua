workspace "Emerald"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "%{wks.location}/src/external/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/src/external/glfw/include"
IncludeDir["Glad"] = "%{wks.location}/src/external/glad/include"
IncludeDir["ImGui"] = "%{wks.location}/src/external/imgui"
IncludeDir["glm"] = "%{wks.location}/src/external/glm"
IncludeDir["stb"] = "%{wks.location}/src/external/stb"

group "Dependencies"
	include "src/external/glfw"
	include "src/external/glad"
	include "src/external/imgui"
group ""

include "src/emerald"
include "src/sandbox"
