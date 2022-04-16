project "GameEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"assets/**"
	}

	includedirs {
		"%{wks.location}/ProEngine/src"	,
		"%{wks.location}/GameEditor/src"	
	}

	links {
		"ProEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "PRO_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "PRO_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "PRO_DIST"
		optimize "On"
