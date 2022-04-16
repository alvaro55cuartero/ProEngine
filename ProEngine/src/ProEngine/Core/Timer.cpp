#include "Propch.h"
#include "ProEngine/Core/Timer.h"
#include "Platform/Windows/WindowsTimer.h"

namespace Pro
{
	Timer* Timer::Create()
	{
#ifdef PRO_PLATFORM_WINDOWS
		return new WindowsTimer();
#else
		HZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}