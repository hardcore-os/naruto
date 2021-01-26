#ifndef KANGAROON_ASYNC_FILE_APPENDER_H_
#define KANGAROON_ASYNC_FILE_APPENDER_H_
#include <vector>
#include "log_appender_interface.h"
#include "count_down_latch.h"
#include "condition.h"
#include "mutex.h"
#include "thread.h"
#include "log_buffer.h"
namespace zoo {
namespace kangaroo {
class AsyncFileAppender : public LogAppenderInterface {
   public:
    AsyncFileAppender(const std::string& basename);
    ~AsyncFileAppender();
    void append(const char* msg, size_t len);
    void start();
    void stop();

   private:
    void threadFunc();

    bool started_;
    bool running_;
    time_t persist_period_;
    std::string basename_;
    Mutex mutex_;
    Condition cond_;
    CountDownLatch countdown_latch_;
    Thread persit_thread_;
    std::unique_ptr<LogBuffer> cur_buffer_;
    std::vector<std::unique_ptr<LogBuffer> > buffers_;
};
}  // namespace kangaroo

}  // namespace zoo

#endif