#ifndef KANGAROO_LOG_H_
#define KANGAROO_LOG_H_
#include <map>
#include <string>
#include <functional>
#include <list>

#include "log_appender_interface.h"
#include "log_config.h"
#include "mutex.h"
#include "singleton.h"
namespace hardcode {
namespace naruto {
static LogConfig kLogConfig;
class Logger {
public:
  static Logger *getLogger() { return Singleton<Logger>::getInstance(); }
  static void setGlobalConfig(const LogConfig &log_config) {
    kLogConfig = log_config;
  }
  template<class F, class... Args> void registerHandle(F&& f, Args&&... args) {
    using RetType = decltype(f(args...)); 
    auto task = std::make_shared<RetType()>(
               std::bind(std::forward<F>(f), std::forward<Args>(args)...)
               );  
    functors_.emplace([task](){
      (*task)();
    });
  }
  void info(const char *format, ...);
  void debug(const char *format, ...);
  void warn(const char *format, ...);
  void error(const char *format, ...);
  void fatal(const char *format, ...);
  /*需要加锁的*/
  void addAppender(const std::string &appender_name,
                   LogAppenderInterface::Ptr appender);
  void delAppender(const std::string &appender_name);
  void clearAppender();

private:
  void writeLog(LogLevel log_level, const char *file_name,
                const char *function_name, int32_t line_num, const char *fmt,
                va_list ap);

private:
  using Task = std::function<void()>;
  Mutex mutex_;
  std::map<std::string, LogAppenderInterface::Ptr> appenders_;
  std::list<Task> functors_;
};
} // namespace naruto

} // namespace hardcode

#define log_fatal(fmt, args...) hardcode::naruto::Logger::fatal(fmt, ##args)
#define log_error(fmt, args...) hardcode::naruto::Logger::error(fmt, ##args)
#define log_warn(fmt, args...) hardcode::naruto::Logger::warn(fmt, ##args)
#define log_debug(fmt, args...) hardcode::naruto::Logger::debug(fmt, ##args)
#define log_info(fmt, args...) hardcode::naruto::Logger::info(fmt, ##args)

#endif