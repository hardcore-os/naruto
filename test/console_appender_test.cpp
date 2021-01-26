#include <iostream>

#include "async_file_appender.h"
#include "log.h"
#include "log_appender_interface.h"
#include "log_config.h"
using namespace hardcode;
using namespace hardcode::naruto;

using namespace std;
class ConsoleAppender : public LogAppenderInterface {
public:
  ConsoleAppender() = default;
  ~ConsoleAppender() = default;
  void append(const char *msg, size_t len) {
    cout << "msg = " << msg << ", len = " << len << endl;
  }
};

int main() {
  LogConfig log_config;
  hardcode::naruto::Logger::setGlobalConfig(log_config);
  // hardcode::naruto::Logger::getLogger()->addAppender(
  //     "console", LogAppenderInterface::Ptr(new ConsoleAppender()));
  hardcode::naruto::Logger::getLogger()->addAppender(
      "asyncfile", LogAppenderInterface::Ptr(new AsyncFileAppender("./lg/")));
  const uint32_t count = 1000;
  for (uint32_t index = 0; index < count; ++index) {
    hardcode::naruto::Logger::getLogger()->fatal("%d hello world", index);
  }
  return 0;
}