#pragma once

#define LOGGER "[Pool System] "

#include <vector>
#include <iostream>
#include "Thread.hpp"
#include <queue>
#include <condition_variable>

#include "Utils/Colors.hpp"
#include "Threading/AtomicMutex.hpp"

namespace NThread {
	typedef std::function<void()> Task;

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

		void registerTask(Task task) {
			taskMtx.lock();
			tasks.push(task);
			taskMtx.unlock();

			tasks_cond.notify_one();
		}

		Task queryTask(Thread* t, std::string pName) {
			queryMtx.lock();

			t->setWorking(false);

			while (tasks.empty()) {
				if (!t->getWorking()) {
					t->setWorking(false);
				}
				// continue
			}

			t->setWorking(true);

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
