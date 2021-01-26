#ifndef NARUTO_UTIL_THREAD_H_
#define NARUTO_UTIL_THREAD_H_
#include <pthread.h>

#include <functional>
namespace hardcode {
namespace naruto {

class Thread {
public:
  using Func = std::function<void(void)>;
  Thread(Func cb, const std::string &name);
  ~Thread();

  bool isStarted();
  void start();
  void join();
  const std::string &getName() const;

  static pid_t CurrentThreadTid();

private:
  static void *threadFuncInternal(void *arg);
  bool started_ = false;
  bool joined_ = false;
  pthread_t tid_;
  std::string name_;
  Func cb_;
};

} // namespace naruto

} // namespace hardcode

#endif