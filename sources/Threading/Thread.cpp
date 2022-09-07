#pragma once

#include "Threading/Thread.hpp"
#include "Threading/PoolSystem.hpp"
#include <iostream>

namespace NThread {
	Thread::Thread(Pool& pPool, const std::string& pName) {
		name = pName + " - Thread";
		std::this_thread::sleep_for(std::chrono::seconds(1));

		thread = std::thread([&]() {
			while (!pPool.shouldThreadStop()) {
				pPool.queryTask(name)();
			}
		});
	}

	Thread::~Thread() {
	}
}
