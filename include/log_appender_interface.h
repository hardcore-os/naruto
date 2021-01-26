#ifndef NARUTO_LOG_APPENDER_INTERFACE_H_
#define NARUTO_LOG_APPENDER_INTERFACE_H_
#include <memory>

namespace hardcode {
namespace naruto {
class LogAppenderInterface {
public:
  using Ptr = std::shared_ptr<LogAppenderInterface>;

public:
  virtual ~LogAppenderInterface() {}
  virtual void append(const char *msg, size_t len) = 0;
};
} // namespace naruto

} // namespace hardcode

#endif