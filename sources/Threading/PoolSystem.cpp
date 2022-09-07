#include "Threading/PoolSystem.hpp"

namespace Thread {
	Pool::Pool() {
	}

	Pool::~Pool() {
		for (auto t : pool)
			delete t;
	}
}
