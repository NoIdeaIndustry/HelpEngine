#pragma once

#include "Threading/Thread.hpp"
#include "Threading/PoolSystem.hpp"
#include <iostream>

namespace NThread {
	Thread::Thread(Pool& pPool, const std::string& pName) {
		name = pName + " - Thread";

		thread = std::thread([&]() {
			while (!pPool.shouldStopPool()) {
				pPool.queryTask(this, name)();
			}
		});
	}

	Thread::~Thread() {
	}
}
