#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace Pro {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		std::mutex m_mutex;
		InstrumentationSession* m_currentSession;
		std::ofstream m_outputStream;
	public:
		Instrumentor()
			: m_currentSession(nullptr)
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(m_mutex);
			if (m_currentSession) {
				InternalEndSession();
			}
			m_outputStream.open(filepath);

			if (m_outputStream.is_open()) {
				m_currentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else {

			}
		}

		void EndSession()
		{
			std::lock_guard lock(m_mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_mutex);
			if (m_currentSession) {
				m_outputStream << json.str();
				m_outputStream.flush();
			}
		}

		static Instrumentor& Get() {
			static Instrumentor instance;
			return instance;
		}

	private:

		void WriteHeader()
		{
			m_outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			m_outputStream.flush();
		}

		void WriteFooter()
		{
			m_outputStream << "]}";
			m_outputStream.flush();
		}

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession() {
			if (m_currentSession) {
				WriteFooter();
				m_outputStream.close();
				delete m_currentSession;
				m_currentSession = nullptr;
			}
		}

	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_name(name), m_stopped(false)
		{
			m_startTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_startTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_stopped = true;
		}
	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::steady_clock> m_startTimepoint;
		bool m_stopped;
	};
}

#define PRO_PROFILE 1
#if PRO_PROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define PRO_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define PRO_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
	#define PRO_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define PRO_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define PRO_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define PRO_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define PRO_FUNC_SIG __func__
	#else
	#define PRO_FUNC_SIG "HZ_FUNC_SIG unknown!"
	#endif

	#define PRO_PROFILE_BEGIN_SESSION(name, filepath) ::Pro::Instrumentor::Get().BeginSession(name, filepath)
	#define PRO_PROFILE_END_SESSION() ::Pro::Instrumentor::Get().EndSession()
	#define PRO_PROFILE_SCOPE(name) ::Pro::InstrumentationTimer timer##__LINE__(name);
	#define PRO_PROFILE_FUNCTION() PRO_PROFILE_SCOPE(PRO_FUNC_SIG)
#else
	#define PRO_PROFILE_BEGIN_SESSION(name, filepath)
	#define PRO_PROFILE_END_SESSION()
	#define PRO_PROFILE_SCOPE(name)
	#define PRO_PROFILE_FUNCTION()
#endif