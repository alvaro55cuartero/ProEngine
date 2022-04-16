#pragma once
#include "ProEngine/Core/Timestep.h"

namespace Pro
{
	class Timer
	{
	public:
		virtual ~Timer() = default;

		virtual void Start() = 0;

		virtual double GetTime() = 0;
		virtual Timestep GetDeltaTime() = 0;
		virtual uint64_t GetTimerValue() = 0;

	public:
		static Timer* Create();
	};
}