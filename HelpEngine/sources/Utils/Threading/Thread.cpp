#pragma once

#include "Utils/Threading/Thread.hpp"
#include "Utils/Threading/PoolSystem.hpp"
#include <iostream>

namespace NThread {
	Thread::Thread(Pool& pPool, const std::string& pName) {
		name = pName + " - Thread";

		thread = std::thread([&]() {
			while (!pPool.shouldStopPool()) {
				pPool.queryMtx.lock();

				while (pPool.tasks.empty()) {
					if (pPool.shouldStopPool())
					{
						pPool.queryMtx.unlock();
						return; 
					}
				}

				ResourceTask rt = pPool.queryResourceTask(name);
				pPool.queryMtx.unlock();
				//std::cout << rt.arg->name << std::endl;
				//if(rt.task == empty))
				
				try
				{
					rt.task(rt.arg);
				}
				catch (const std::exception&)
				{
					continue;
				}
				
			}
		});
	}

	Thread::~Thread() {
		thread.join();
	}
}
