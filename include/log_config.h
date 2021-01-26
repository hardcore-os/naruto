#ifndef NARUTO_LOG_CONFIG_H_
#define NARUTO_LOG_CONFIG_H_

#include <stdint.h>
#include <string>

#include "file_writer_type.h"
#include "log_level.h"
namespace hardcode {
namespace naruto {
struct LogConfig {
  uint32_t log_buffer_size = 4000;
  uint32_t log_buffer_nums = 2;
  LogLevel log_level = LogLevel::INFO;
  struct FileOption {
    std::string file_path;
    //日志滚动大小和时间间隔，仅限asyncfileappender
    uint32_t log_flush_file_size;
    uint32_t log_flush_interval;
    FileWriterType file_writer_type;

  } file_option;
};
} // namespace naruto

} // namespace hardcode

#endif