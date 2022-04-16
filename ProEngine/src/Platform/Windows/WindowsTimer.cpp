#include "Propch.h"
#include "WindowsTimer.h"

namespace Pro
{

	WindowsTimer::WindowsTimer()
		:m_start{ 0 }, m_frequency{ 0 }, m_last{0}
	{
		if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency) == 0) {
			std::cout << "error";
		}
	}

	void WindowsTimer::Start() {
		QueryPerformanceCounter(&m_start);
		m_last = m_start;
	}

	Timestep WindowsTimer::GetDeltaTime() {
		LARGE_INTEGER current, elapsed;

		QueryPerformanceCounter(&current);
		elapsed.QuadPart = current.QuadPart - m_last.QuadPart;
		m_last = current;

		elapsed.QuadPart *= 1000000;
		elapsed.QuadPart /= m_frequency.QuadPart;

		return (double)elapsed.QuadPart;
	}


	double WindowsTimer::GetTime() {
		return 0; //(double)((GetTimerValue() - m_offset)); // m_frequency);
	}

	uint64_t WindowsTimer::GetTimerValue() {
		uint64_t value;
		QueryPerformanceCounter((LARGE_INTEGER*)&value);
		return value;
	}
}