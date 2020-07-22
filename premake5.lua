workspace "Engine"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputDir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

project "Engine"
	location "Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("out/" .. outputDir .. "/%{prj.name}")
	objdir ("out_tmp/" .. outputDir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS",
			"BUILD_DLL"
		}

		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../out/" .. outputDir .. "/GameDemo/"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "ENGINE_DIST"
		optimize "On"

project "GameDemo"
	location "GameDemo"
	kind "ConsoleApp"
	language "C++"

	targetdir ("out/" .. outputDir .. "/%{prj.name}")
	objdir ("out_tmp/" .. outputDir .. "/%{prj.name}")

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
		symbols "On"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "ENGINE_DIST"
		optimize "On"