project "ProEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Propch.h"
	pchsource "src/Propch.cpp"

	files {
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/EnTT/**.hpp",
		"vendor/EnTT/**.cpp",
		"vendor/box2d/src/**.h",
		"vendor/box2d/src/**.cpp",
		"vendor/json/single_include/**.hpp"

	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"src",
		"vendor/stb_image",
		"vendor/GLFW/include",
		"vendor/Glad/include",
		"vendor/ImGui",
		"vendor/glm",
		"vendor/EnTT/include",
		"vendor/json/single_include",
		"C:/VulkanSDK/1.3.204.0/Include",
		"vendor/FBXImporter/include",
		"vendor/box2d/include"
	}

	libdirs { 
		"C:/VulkanSDK/1.3.204.0/Lib",
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"vulkan-1.lib"
	}


	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "PRO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PRO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PRO_DIST"
		runtime "Release"
		optimize "on"
