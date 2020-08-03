workspace "Engine"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

includeDir = {}
includeDir["GLFW"] = "Engine/vendor/GLFW/include"
includeDir["Glad"] = "Engine/vendor/Glad/include"

include "Engine/vendor/GLFW"
include "Engine/vendor/Glad"

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("out/" .. outputdir .. "/%{prj.name}")
	objdir ("out_tmp/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Engine/src/pch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS",
			"BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../out/" .. outputdir .. "/GameDemo/"
		}

	filter "configurations:Debug"
		defines 
		{
			"ENGINE_DEBUG",
			"ENABLE_ASSERT"
		}
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "ENGINE_DIST"
		buildoptions "/MD"
		optimize "On"

project "GameDemo"
	location "GameDemo"
	kind "ConsoleApp"
	language "C++"

	targetdir ("out/" .. outputdir .. "/%{prj.name}")
	objdir ("out_tmp/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/src"
	}

	links 
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "ENGINE_DIST"
		buildoptions "/MD"
		optimize "On"