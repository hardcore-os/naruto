#include "thread.h"

#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

#include <atomic>
namespace zoo {
namespace kangaroo {

std::atomic<int> thread_count(0);
static __thread pid_t t_tid = 0;

pid_t Thread::CurrentThreadTid() {
    if (t_tid == 0) {
        t_tid = ::syscall(SYS_gettid);
    }
    return t_tid;
}

Thread::Thread(Func cb, const std::string& name)
    : started_(false), joined_(false), cb_(std::move(cb)) {
    if (name.empty()) {
        int num = thread_count.fetch_add(1);
        char buf[30];
        snprintf(buf, sizeof buf, "Thread-%d", num);
        name_ = buf;
    } else {
        name_ = name;
    }
}

Thread::~Thread() {
    if (started_ && !joined_) {
        pthread_detach(tid_);
    }
}

bool Thread::isStarted() { return started_; }

void Thread::start() {
    started_ = true;
    if (pthread_create(&tid_, nullptr, Thread::threadFuncInternal, this) == 0) {
        started_ = false;
    }
}

void Thread::join() {
    joined_ = true;
    if (pthread_join(tid_, nullptr) == 0) {
        joined_ = false;
    }
}

const std::string& Thread::getName() const { return name_; }

void* Thread::threadFuncInternal(void* arg) {
    Thread* thread = static_cast<Thread*>(arg);
    Func cb;
    cb.swap(thread->cb_);
    cb();
    return 0;
}
}  // namespace kangaroo
}  // namespace zoo