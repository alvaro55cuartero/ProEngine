#pragma once

#include "ProEngine/Core/PlatformDetection.h"
#include "ProEngine/Debug/Instrumentor.h"

#include <functional>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <array>

#include "ProEngine/Core/Base.h"


#ifdef PRO_PLATFORM_WINDOWS
	#include <Windows.h>
	#include <xinput.h>
	#include <windowsx.h>

#endif

#include "vulkan/vulkan.h"




