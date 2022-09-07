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
			{
				std::lock_guard<std::mutex> tasks_guard{ tasksLock };
				tasks.push(task);
			}
			taskCondition.notify_one();
		}

		Task queryTask(std::string pName) {
			std::cout << "\"" << pName << "\"" << " is asking for a task..." << std::endl;

			std::unique_lock<std::mutex> tasks_guard{ tasksLock };
			while (tasks.empty())
				taskCondition.wait(tasks_guard);

			std::cout << "\"" << pName << "\"" << " found a task!" << std::endl;

			Task task = tasks.front();
			tasks.pop();
			tasks_guard.unlock();
			return task;
		}

		bool isRegistering = true;
	private:
		std::atomic_bool shouldThreadsStops{ false };
		std::vector<Thread*> pool;
		std::mutex tasksLock;
		std::condition_variable taskCondition;
		std::queue<Task> tasks;
	};
}
