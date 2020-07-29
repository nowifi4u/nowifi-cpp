#pragma once

#include <time.h>
#include <chrono>

namespace nw {

	template <class Clock>
	class Time {
	public:

		Time() = delete;
		Time(const Time&) = delete;
		~Time() = delete;

		static inline time_t ctime() {
			return time(NULL);
		}



		static inline auto now() {
			return Clock::now().time_since_epoch();
		}

		static inline long long nowMicro() {
			return std::chrono::duration_cast<std::chrono::microseconds>(now()).count();
		}

		static inline long long nowMilli() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(now()).count();
		}
	};

	using SystemTime = Time<std::chrono::system_clock>;
	using HighresClock = Time<std::chrono::high_resolution_clock>;
	using SteadyClock = Time<std::chrono::steady_clock>;

} // namespace nw