#pragma once

#include <chrono>


#define PROFILE_SCOPE(name) Profiler Profiler##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

namespace Pro 
{
		
	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

		
	template<typename Fn>
	class Profiler
	{
	public:
		Profiler(const char* name, Fn&& func)
			: m_name(name), m_func(func), m_stopped(false)
		{
			m_startTimepoint = std::chrono::high_resolution_clock::now();
		}

		~Profiler()
		{
			if (!m_stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			m_stopped = true;

			float duration = (end - start) * 0.001f;

			std::cout << "Timer: " << duration << "\n";

			m_func({ m_name, duration });
		}


	private:
		const char* m_name;
		Fn m_func;
		std::chrono::time_point<std::chrono::steady_clock> m_startTimepoint;
		bool m_stopped;
	};
}