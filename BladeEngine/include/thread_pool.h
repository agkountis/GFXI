#ifndef BLADE_THREAD_POOL_H
#define BLADE_THREAD_POOL_H
#include <thread>
#include <vector>
#include <queue>
#include <mutex>

namespace Blade
{
	class ThreadPool
	{
	private:
		std::vector<std::thread> m_Workers;

		std::queue<std::function<void()>> m_Tasks;

		mutable std::mutex m_TaskMutex;

		std::condition_variable m_HasTasks;

		std::condition_variable m_TasksDone;

		bool m_Stop{ false };

		size_t m_ActiveTasks{ 0 };

		void WaitAndExecude();

	public:

		~ThreadPool();

		bool Initialize();

		void Wait();

		void Terminate();

		void AddTask(std::function<void()> job);

		void AddTasks(const std::vector<std::function<void()>> &jobs);

		size_t QueuedTaskCount() const;

		size_t ActiveTaskCount() const;

		size_t PendingTaskCount() const;
	};
}

#endif //BLADE_THREAD_POOL_H
