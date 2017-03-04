#ifndef BLADE_TIMER_H_
#define BLADE_TIMER_H_
#include <chrono>

namespace Blade
{
	template <typename T>
	using TimePoint = std::chrono::time_point<T>;

	using HighResolutionClock = std::chrono::high_resolution_clock;

	using HighResolutionTimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;


	class Timer
	{
	private:
		HighResolutionTimePoint m_Start;
		HighResolutionTimePoint m_Pause;

		mutable HighResolutionTimePoint m_Prev;

		bool m_Running;

	public:
		Timer() : m_Prev{ HighResolutionClock::now() }, m_Running{ false }
		{
		}

		void Reset() noexcept
		{
			m_Pause = {};
			m_Start = HighResolutionClock::now();
		}

		void Start() noexcept
		{
			if (!IsRunning())
			{
				m_Start += HighResolutionClock::now() - m_Pause;
				m_Pause = {};

				m_Running = true;
			}
		}

		void Stop() noexcept
		{
			if (IsRunning())
			{
				m_Pause = HighResolutionClock::now();

				m_Running = false;
			}
		}

		bool IsRunning() const noexcept
		{
			return m_Running;
		}

		long long GetMsec() const noexcept
		{
			using namespace std::chrono;
			if (!IsRunning())
			{
				// in paused state...
				return duration_cast<milliseconds>(m_Pause - m_Start).count();
			}

			return duration_cast<milliseconds>(HighResolutionClock::now() - m_Start).count();
		}

		double GetSec() const noexcept
		{
			using namespace std::chrono;
			if (!IsRunning())
			{
				// in paused state...
				return duration<double>{ m_Pause - m_Start }.count();
			}

			return duration<double>{ HighResolutionClock::now() - m_Start }.count();
		}

		double GetDelta() const noexcept
		{
			using namespace std::chrono;

			duration<double> dur{ HighResolutionClock::now() - m_Prev };
			m_Prev = HighResolutionClock::now();

			return dur.count();
		}
	};
}

#endif //BLADE_TIMER_H_
