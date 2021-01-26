#ifndef KANGAROON_UTIL_CONDITION_H_
#define KANGAROON_UTIL_CONDITION_H_
#include <pthread.h>
#include <stdint.h>
#include "mutex.h"
namespace zoo {

namespace kangaroo {
class Condition {
   public:
    explicit Condition(Mutex& mutex);
    ~Condition();

    void wait();
    bool waitForSeconds(int32_t seconds);
    void notifyOne();
    void notifyAll();

   private:
    Mutex& mutex_;
    pthread_cond_t condvar_;
};

}  // namespace kangaroo

}  // namespace zoo

#endif