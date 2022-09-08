#pragma once

#include <vector>
#include "Thread.hpp"
#include <iostream>
#include "Utils/Colors.hpp"
#include <queue>
#include "Threading/AtomicMutex.hpp"
#include <condition_variable>

#define LOGGER "[Pool System] "

namespace NThread {
	typedef std::function<void()> Task;

	class Pool
	{
	public:
		Pool();
		~Pool();

		std::vector<Thread*> getPool() 
		{
			return pool;
		}

		void registerThread(Thread* t) 
		{
			pool.push_back(t);
		}

		void unregisterThread(Thread& t) 
		{
			for (int i = 0; i < pool.size(); i++) {
				if (t.getName() == pool.at(i)->getName()) {
					pool.erase(pool.begin() + i);
					break;
				}
			}
		}

		void stopThreads() 
		{
			shouldThreadsStops = true;
		}

		bool shouldThreadStop() 
		{
			return shouldThreadsStops;
		}

		void registerTask(Task task) {
			taskMtx.lock();
			tasks.push(task);
			taskMtx.unlock();

			tasks_cond.notify_one();
		}

		Task queryTask(std::string pName) {
			queryMtx.lock();

			while (tasks.empty());

			Task task = tasks.front();
			tasks.pop();
			queryMtx.unlock();
			return task;
		}

		bool isRegistering = true;
	private:
		AtomicMutex queryMtx;
		AtomicMutex taskMtx;

		std::atomic_bool shouldThreadsStops{ false };
		std::vector<Thread*> pool;
		std::queue<Task> tasks;

		std::condition_variable tasks_cond;
	};
}
