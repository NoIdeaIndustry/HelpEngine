#pragma once

#define LOGGER "[Pool System] "

#include <vector>
#include <iostream>
#include "Thread.hpp"
#include <queue>
#include <condition_variable>
#include "Resources/Resource.hpp"
#include "Utils/Colors.hpp"
#include "Threading/AtomicMutex.hpp"

namespace NThread {
	
	struct ResourceTask
	{
		std::function<void(Resources::Resource*)> task;
		Resources::Resource* arg;
	};

	class Pool
	{
	public:
		Pool();
		~Pool();

		std::vector<Thread*> getPool() {
			return pool;
		}

		void registerThread(Thread* t) {
			pool.push_back(t);
		}

		void unregisterThread(Thread& t) {
			for (int i = 0; i < pool.size(); i++) {
				if (t.getName() == pool.at(i)->getName()) {
					pool.erase(pool.begin() + i);
					break;
				}
			}
		}

		void stopPool() {
			shouldThreadsStops = true;
		}

		bool shouldStopPool() {
			return shouldThreadsStops;
		}

		void registerTask(ResourceTask task) {
			taskMtx.lock();
			tasks.push(task);
			taskMtx.unlock();

			tasks_cond.notify_one();
		}

		ResourceTask queryResourceTask(std::string pName) {

			ResourceTask task = tasks.front();
			tasks.pop();
			return task;
		}

		bool isRegistering = true;
		AtomicMutex queryMtx;
		std::queue<ResourceTask> tasks;
	private:
		AtomicMutex taskMtx;

		std::atomic_bool shouldThreadsStops{ false };
		std::vector<Thread*> pool;

		std::condition_variable tasks_cond;
	};
}
