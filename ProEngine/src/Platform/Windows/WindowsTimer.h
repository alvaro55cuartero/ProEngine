#pragma once
#include "ProEngine/Core/Timer.h"

namespace Pro
{
	class WindowsTimer : public Timer
	{
	public:
		WindowsTimer();

		virtual void Start() override;
		virtual double GetTime() override;
		virtual Timestep GetDeltaTime() override;
		virtual uint64_t GetTimerValue() override;

	private:
		LARGE_INTEGER m_start;
		LARGE_INTEGER m_frequency;
		LARGE_INTEGER m_last;
	};

}
