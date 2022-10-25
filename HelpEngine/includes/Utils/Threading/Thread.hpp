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

		bool getWorking() {
			return isWorking;
		}

		void setWorking(const bool& pIsWorking) {
			isWorking = pIsWorking;
		}

	private:
		std::string name;
		std::thread thread;

		bool isWorking = false;
	};
}
