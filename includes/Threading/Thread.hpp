#pragma once

#include <string>
#include <thread>
#include <functional>

namespace NThread {
	class Pool;

	class Thread
	{
	public:
		Thread(Pool& pPool, const std::string& pName);
		~Thread();

		std::string getName() {
			return name;
		}

		std::thread& getThread() {
			return thread;
		}

		void registerTask(std::function<void()> pTask);

	private:
		std::string name;
		std::thread thread;
	};
}
