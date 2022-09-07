#pragma once

#include <vector>
#include "Thread.hpp"
#include <iostream>
#include "Utils/Colors.hpp"
#include <queue>
#include <mutex>

#define LOGGER "[Pool System] "

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

			std::cout << ESC << RED << LOGGER << "Registered Thread: | Id: " << t->getThread().get_id() << " | Name: \"" << t->getName() << "\"" << RESET << std::endl;
		}

		void unregisterThread(Thread& t) {
			for (int i = 0; i < pool.size(); i++) {
				if (t.getName() == pool.at(i)->getName()) {
					pool.erase(pool.begin() + i);
					break;
				}
			}
		}

		void stopThreads() {
			shouldThreadsStops = true;
		}

		bool shouldThreadStop() {
			return shouldThreadsStops;
		}

		void runTask(Task task) {
			while (lockRun.test_and_set(std::memory_order_acquire)) {
				tasks.push(task);
				lockRun.clear(std::memory_order_release);
			}
			taskCondition.notify_one();
		}

		Task queryTask(std::string pName) {
			std::cout << "\"" << pName << "\"" << " is asking for a task..." << std::endl;

			while (lockQuery.test_and_set(std::memory_order_acquire)) {
				while (tasks.empty()) {
					taskCondition.wait_until(lockQuery);
				}
			}

			std::cout << "\"" << pName << "\"" << " found a task!" << std::endl;

			Task task = tasks.front();
			tasks.pop();
			lockQuery.clear(std::memory_order_release);
			return task;
		}

		bool isRegistering = true;
	private:
		std::atomic_flag lockQuery = ATOMIC_FLAG_INIT;
		std::atomic_flag lockRun = ATOMIC_FLAG_INIT;

		std::atomic_bool canGoThru{ false };
		std::atomic_bool shouldThreadsStops{ false };

		std::vector<Thread*> pool;
		std::queue<Task> tasks;
	};
}
