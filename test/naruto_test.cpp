#include "async_file_appender.h"
#include "log.h"
#include "log_appender_interface.h"
#include "log_config.h"
#include "gtest/gtest.h"
#include <chrono>
#include <iostream>

TEST(Benchmarks, append) {
  LogConfig log_config;
  hardcode::naruto::Logger::setGlobalConfig(log_config);
  hardcode::naruto::Logger::getLogger()->addAppender(
      "asyncfile", LogAppenderInterface::Ptr(new AsyncFileAppender("./lg/")));
  const int32_t count = 100000;
  auto start = std::chrono::system_clock::now();
  for (int32_t index = 0; index < count; ++index) {
    hardcode::naruto::Logger::getLogger()->fatal("%d hello world", index);
  }
  auto end = std::chrono::system_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << count << "次运行耗时" << duration.count() << "us" << std::endl;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
