#include "Threading/PoolSystem.hpp"

namespace NThread {
	Pool::Pool() {
	}

	Pool::~Pool() {
		for (auto t : pool)
			delete t;
	}
}
