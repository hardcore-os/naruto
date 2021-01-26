#include "condition.h"

#include <errno.h>
#include <stdint.h>

 
using namespace zoo;
using namespace zoo::kangaroo;
Condition::Condition(Mutex& mutex)
	:mutex_(mutex) {
	pthread_cond_init(&condvar_, nullptr);
}

Condition::~Condition() {
	pthread_cond_destroy(&condvar_);
}

void Condition::wait() {
	pthread_cond_wait(&condvar_, mutex_.getMutex());
}

bool Condition::waitForSeconds(int32_t seconds) {
	struct timespec abstime;
	clock_gettime(CLOCK_REALTIME, &abstime);

	const int64_t kNanoSecondsPerSecond = 1000000000;
	int64_t nanoseconds = static_cast<int64_t>(seconds * kNanoSecondsPerSecond);

	abstime.tv_sec += static_cast<time_t>((abstime.tv_nsec + nanoseconds) / kNanoSecondsPerSecond);
	abstime.tv_nsec = static_cast<long>((abstime.tv_nsec + nanoseconds) % kNanoSecondsPerSecond);
	return ETIMEDOUT == pthread_cond_timedwait(&condvar_, mutex_.getMutex(), &abstime);
}

void Condition::notifyOne() {
	pthread_cond_signal(&condvar_);
}

void Condition::notifyAll() {
	pthread_cond_broadcast(&condvar_);
}
 
