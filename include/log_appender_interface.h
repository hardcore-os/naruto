#ifndef KANGAROON_LOG_APPENDER_INTERFACE_H_
#define KANGAROON_LOG_APPENDER_INTERFACE_H_
#include <memory>

namespace zoo {
namespace kangaroo {
class LogAppenderInterface {
   public:
    using Ptr = std::shared_ptr<LogAppenderInterface>;

   public:
    virtual ~LogAppenderInterface() {}
    virtual void append(const char* msg, size_t len) = 0;
};
}  // namespace kangaroo

}  // namespace zoo

#endif