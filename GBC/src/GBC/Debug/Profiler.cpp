#include "gbcpch.h"
#include "Profiler.h"

namespace gbc
{
	InstrumentationSession::InstrumentationSession(const std::string& name)
		: name(name) {}

	void Profiler::BeginSession(const std::string& name, const std::string& filepath)
	{
		std::lock_guard lock(mutex);

		if (currentSession != nullptr)
			InternalEndSession();

		// Create any directories that need to be created before opening the file
		for (size_t beginIndex = 0, endIndex = 0; (endIndex = filepath.find_first_of("/\\", beginIndex)) != std::string::npos; beginIndex = endIndex + 1)
			if (beginIndex != endIndex)
				std::filesystem::create_directory(filepath.substr(beginIndex, endIndex - beginIndex));

		outputStream.open(filepath);
		if (outputStream.is_open())
		{
			currentSession = new InstrumentationSession(name);
			WriteHeader();
		}
	}

	void Profiler::EndSession()
	{
		std::lock_guard lock(mutex);
		InternalEndSession();
	}

	void Profiler::WriteProfile(const ProfileResult& result)
	{
		std::lock_guard lock(mutex);
		if (currentSession != nullptr)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << result.elapsedTime.count() << ',';
			json << "\"name\":\"" << result.name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.threadID << ',';
			json << "\"ts\":" << result.start.count();
			json << '}';

			outputStream << json.str();
			outputStream.flush();
		}
	}

	Profiler& Profiler::Get()
	{
		static Profiler instance;
		return instance;
	}

	Profiler::~Profiler()
	{
		EndSession();
	}

	void Profiler::WriteHeader()
	{
		outputStream << "{\"otherData\":{},\"traceEvents\":[{}";
		outputStream.flush();
	}

	void Profiler::WriteFooter()
	{
		outputStream << "]}";
		outputStream.flush();
	}

	void Profiler::InternalEndSession()
	{
		if (currentSession != nullptr)
		{
			WriteFooter();
			outputStream.close();
			delete currentSession;
			currentSession = nullptr;
		}
	}

	ProfilerTimer::ProfilerTimer(const char* name)
		: name(name), stopped(false), startTimepoint(std::chrono::steady_clock::now()) {}

	ProfilerTimer::~ProfilerTimer()
	{
		if (!stopped)
			Stop();
	}

	void ProfilerTimer::Stop()
	{
		auto endTimepoint = std::chrono::steady_clock::now();
		FloatingPointMicroseconds highResStart = startTimepoint.time_since_epoch();
		auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch();

		Profiler::Get().WriteProfile({name, highResStart, elapsedTime, std::this_thread::get_id()});

		stopped = true;
	}
}
