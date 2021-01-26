#include <iostream>

#include "log.h"
#include "log_appender_interface.h"
#include "log_config.h"
#include "async_file_appender.h"
using namespace zoo;
using namespace zoo::kangaroo;

using namespace std;
class ConsoleAppender : public LogAppenderInterface {
   public:
    ConsoleAppender() = default;
    ~ConsoleAppender() = default;
    void append(const char* msg, size_t len) { cout <<"msg = "<< msg <<", len = " << len<< endl; }
};

int main() {
    LogConfig log_config;
    zoo::kangaroo::Logger::setGlobalConfig(log_config);
    // zoo::kangaroo::Logger::getLogger()->addAppender(
    //     "console", LogAppenderInterface::Ptr(new ConsoleAppender()));
        zoo::kangaroo::Logger::getLogger()->addAppender(
        "asyncfile", LogAppenderInterface::Ptr(new AsyncFileAppender("./lg/")));
    const uint32_t count = 1000;
    for (uint32_t index = 0 ;index < count ; ++index ) {
        zoo::kangaroo::Logger::getLogger()->fatal("%d hello world", index);
    }
    return 0;
}