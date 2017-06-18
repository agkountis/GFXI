#ifndef BLADE_THREAD_POOL_H
#define BLADE_THREAD_POOL_H
#include <thread>
#include <vector>
#include <queue>
#include <mutex>

namespace Blade
{
	/**
	\brief ThreadPool class of the engine.
	\details This class can be use to efficiently execute 
	asynchronous callbacks on the application. It provides methods to manage 
	the worker threads.
	*/
	class ThreadPool
	{
	private:
		/**
		\brief The worker threads pool
		*/
		std::vector<std::thread> m_Workers;

		/**
		\brief the asynchronous callbacks that need to be executed by the thread pool
		*/
		std::queue<std::function<void()>> m_Tasks;

		/**
		\brief Mutex by the thread to assure that the task assignment is safe.
		*/
		mutable std::mutex m_TaskMutex;

		std::condition_variable m_HasTasks;

		std::condition_variable m_TasksDone;

		bool m_Stop{ false };

		size_t m_ActiveTasks{ 0 };

		void WaitAndExecude();

	public:
		~ThreadPool();

		/**
		\brief Initialize the thread pool
		\details Creates the workers.
		*/
		bool Initialize();


		/**
		\brief Wait function of the thread pool
		*/
		void Wait();

		/**
		\brief Shutdown the thread pool
		*/
		void Terminate();

		/**
		\brief Add new task to the task queue.
		\param job The new task that need to be added
		*/
		void AddTask(std::function<void()> job);

		/**
		\brief Add a new collection of task to the task queue.
		\param jobs The vector of the task that need to be added
		*/
		void AddTasks(const std::vector<std::function<void()>> &jobs);

		/**
		\brief Returns the number of queue task
		\return The number of tasks in the queue
		*/
		size_t QueuedTaskCount() const;

		/**
		\brief Returns the number of the task currently active
		\return The number of the task in process.
		*/
		size_t ActiveTaskCount() const;

		/**
		\brief Return the pending task count
		\return The number of pending task (activeTask + tasks in the queue).
		*/
		size_t PendingTaskCount() const;
	};
}

#endif //BLADE_THREAD_POOL_H
