#pragma once

// static profiler

#include "axt/Core.h"

#include <fstream>
#include <chrono>

namespace profiling {
	class Profile {

	public:
		Profile(const char* name) : mName{ name }, mStopped{ false } {}
		~Profile();
		void Stop();
	private:
		const char* mName;
		std::chrono::high_resolution_clock::time_point mStartTime{ std::chrono::high_resolution_clock::now() };
		bool mStopped;
	};
	
	class ProfileSession {
	private:
		struct ProfileData {
			const char* name;
			long long mStart, mEnd;
		};
	public:
		static void Begin(const char* sessionName, const char* filepath = "ProfilerResults.json");
		static void End();
		static void WriteData(const ProfileData& data);
	private:
		static void Header();
		static void Footer();
		static ProfileSession mInstance;
		std::ofstream mFileStream;
		int mProfileCount{ 0 };
	};
}

#define A_PROFILING_ENABLED false
#if A_PROFILING_ENABLED
	#define A_PROFILE_NEW_SESSION(name, filepath) profiling::ProfileSession::Begin(name, filepath)
	#define A_PROFILE_END_SESSION() profiling::ProfileSession::End()
	#define A_PROFILE_SCOPE(name) profiling::Profile profile##__LINE__{name}
	#define A_PROFILE_FUNCTION() A_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define A_PROFILE_NEW_SESSION(name, filepath)
	#define A_PROFILE_END_SESSION()
	#define A_PROFILE_SCOPE(name)
	#define A_PROFILE_FUNCTION()
#endif
