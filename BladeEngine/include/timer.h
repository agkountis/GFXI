#ifndef BLADE_TIMER_H_
#define BLADE_TIMER_H_
#include <chrono>

namespace Blade
{
	template <typename T>
	using TimePoint = std::chrono::time_point<T>;

	using HighResolutionClock = std::chrono::high_resolution_clock;

	using HighResolutionTimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

	/**
	\brief Timer class of the engine
	\details Provides chronometer functionalities.
	*/
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

		/**
		\brief Reset the timer.
		*/
		void Reset() noexcept
		{
			m_Pause = {};
			m_Start = HighResolutionClock::now();
		}

		/**
		\brief Start the timer
		*/
		void Start() noexcept
		{
			if (!IsRunning())
			{
				m_Start += HighResolutionClock::now() - m_Pause;
				m_Pause = {};

				m_Running = true;
			}
		}

		/**
		\brief Stop the timer.
		*/
		void Stop() noexcept
		{
			if (IsRunning())
			{
				m_Pause = HighResolutionClock::now();

				m_Running = false;
			}
		}

		/**
		\brief Getter for the timer running-flag
		\return TRUE if the timer is running, false otherwise
		*/
		bool IsRunning() const noexcept
		{
			return m_Running;
		}

		/**
		\brief Return the elapsed time in milliseconds.
		\return Elapsed time in milliseconds
		*/
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

		/**
		\brief Return the elapsed time in seconds.
		\return Elapsed time in seconds
		*/
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

		/**
		\brief Returns delta time
		\return delta time.
		*/
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
