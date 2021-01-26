#ifndef NARUTO_LOG_LEVEL_H_
#define NARUTO_LOG_LEVEL_H_
#include <stdint.h>

namespace hardcode {
namespace naruto {
enum class LogLevel : uint8_t {
  TRACE = 0,
  DEBUG = 1,
  INFO = 2,
  WARN = 3,
  ERROR = 4,
  FATAL = 5
};
} // namespace naruto

} // namespace hardcode

#endif