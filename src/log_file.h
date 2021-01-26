#ifndef NARUTO_LOG_FILE_H_
#define NARUTO_LOG_FILE_H_
#include <memory>
#include <string>
#include <sys/time.h>

#include "file_writer_type.h"
namespace hardcode {
namespace naruto {
class FileWriter {
public:
  FileWriter() = default;
  virtual ~FileWriter() = default;
  virtual void append(const char *msg, int32_t len) = 0;
  virtual void flush() = 0;
  virtual uint32_t writtenBytes() const = 0;
};
class LogFile {
public:
  LogFile(const std::string &basename, int32_t roll_size,
          int32_t flush_interval, int32_t check_interval,
          FileWriterType file_writer_type);
  ~LogFile();

  void append(const char *logline, int32_t len);
  void flush();
  bool rollFile();

private:
  std::string basename_;
  uint32_t roll_size_;
  uint32_t flush_interval_;
  //多久进行检查一次，因为可能日志没满，但是跨天了
  uint32_t check_freq_count_;
  uint32_t count_;
  time_t start_of_period_;
  time_t last_roll_;
  time_t last_flush_;
  std::shared_ptr<FileWriter> file_;
  FileWriterType file_writer_type_;
  constexpr static int kRollPerSeconds = 60 * 60 * 24;
};
} // namespace naruto

} // namespace hardcode

#endif