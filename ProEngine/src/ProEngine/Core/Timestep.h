#pragma once

namespace Pro 
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time / 1000000.0f; }

		float GetSeconds() const { return m_Time / 1000000.0f; }
		float GetMilliseconds() const { return m_Time / 1000.0f; }
	private:
		float m_Time;
	};
}
