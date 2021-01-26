#ifndef NARUTO_UTIL_CONDITION_H_
#define NARUTO_UTIL_CONDITION_H_
#include <pthread.h>
#include <stdint.h>

#include "mutex.h"
namespace hardcode {

namespace naruto {
class Condition {
public:
  explicit Condition(Mutex &mutex);
  ~Condition();

  void wait();
  bool waitForSeconds(int32_t seconds);
  void notifyOne();
  void notifyAll();

private:
  Mutex &mutex_;
  pthread_cond_t condvar_;
};

} // namespace naruto

} // namespace hardcode

#endif