workspace "ProEngine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "3party"
	include "ProEngine/vendor/GLFW"
	include "ProEngine/vendor/glad"
	include "ProEngine/vendor/imgui"
group ""



include "ProEngine"
include "SandBox"
include "Game"
include "ProCircuit"
include "GameEditor"

