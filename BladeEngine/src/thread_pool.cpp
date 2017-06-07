#include "thread_pool.h"
#include "trace.h"
#include <string>

namespace Blade
{
	ThreadPool::~ThreadPool()
	{
		Terminate();
	}

	void ThreadPool::WaitAndExecude()
	{
		std::function<void()> task;

		while (true)
		{
			{
				/**
				* Acquire the mutex.
				*/
				std::unique_lock<std::mutex> lock(m_TaskMutex);

				/**
				* The thread waits until jobs exists in the queue.
				*/
				m_HasTasks.wait(lock, [this] {
					return !m_Tasks.empty() || m_Stop;
				});

				if (m_Stop)
				{
					std::cout << "Thread terminating." << std::endl;
					return;
				}

				/**
				* Get the job in the front of the queue.
				*/
				task = m_Tasks.front();

				m_Tasks.pop();

				++m_ActiveTasks;
			}

			/**
			* Execute the task.
			*/
			task();

			{
				std::lock_guard<std::mutex> lock(m_TaskMutex);

				--m_ActiveTasks;

				if (m_Tasks.empty())
				{
					m_TasksDone.notify_all();
				}
			}
		}

	}

	bool ThreadPool::Initialize()
	{
		BLADE_TRACE("Initializing thread pool...");

		/**
		* Get the system's supported thread count.
		*/
		int thread_count = std::thread::hardware_concurrency();

		if (!thread_count) {
			BLADE_ERROR("Not able to detect the system's available thread count!");
			return false;
		}

		BLADE_TRACE("Available system threads: " + std::to_string(thread_count));

		BLADE_TRACE("Creating workers...");

		/**
		* Spawn the worker threads.
		*/
		for (int i = 0; i < thread_count; i++) {

			/**
			* The workers will execute an infinite loop function
			* and will wait for a job to enter the job queue. Once a job is in the the queue
			* the threads will wake up to acquire and execute it.
			*/
			m_Workers.emplace_back(&ThreadPool::WaitAndExecude, this);
		}

		return true;
	}


	void ThreadPool::Wait()
	{
		std::unique_lock<std::mutex> lock(m_TaskMutex);

		m_TasksDone.wait(lock, [this] {
			return m_Tasks.empty() && m_ActiveTasks == 0;
		});
	}

	void ThreadPool::Terminate()
	{
		if (!m_Workers.empty())
		{
			{
				std::lock_guard<std::mutex> lock(m_TaskMutex);

				while (!m_Tasks.empty())
				{
					m_Tasks.pop();
				}

				m_Stop = true;

				m_HasTasks.notify_all();
			}

			for (auto &worker : m_Workers) {
				worker.join();
			}
		}
	}

	void ThreadPool::AddTask(std::function<void()> job)
	{
		std::lock_guard<std::mutex> lock(m_TaskMutex);

		m_Tasks.push(job);

		m_HasTasks.notify_one();
	}


	void ThreadPool::AddTasks(const std::vector<std::function<void()>> &jobs)
	{
		std::lock_guard<std::mutex> lock(m_TaskMutex);

		for (auto &job : jobs) {
			this->m_Tasks.push(std::move(job));
		}

		m_HasTasks.notify_all();
	}

	size_t ThreadPool::QueuedTaskCount() const
	{
		std::lock_guard<std::mutex> lock(m_TaskMutex);

		return m_Tasks.size();
	}

	size_t ThreadPool::ActiveTaskCount() const
	{
		std::lock_guard<std::mutex> lock(m_TaskMutex);

		return m_ActiveTasks;
	}


	size_t ThreadPool::PendingTaskCount() const
	{
		std::lock_guard<std::mutex> lock(m_TaskMutex);

		return m_ActiveTasks + m_Tasks.size();
	}
}
