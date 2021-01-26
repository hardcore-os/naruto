#include "async_file_appender.h"

#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

#include "log.h"
#include "log_buffer.h"
#include "log_file.h"
namespace hardcode {
namespace naruto {

AsyncFileAppender::AsyncFileAppender(const std::string &basename)
    : started_(false), running_(false),
      persist_period_(kLogConfig.file_option.log_flush_interval),
      basename_(basename), cond_(mutex_), countdown_latch_(1),
      persit_thread_(std::bind(&AsyncFileAppender::threadFunc, this),
                     "AsyncLogging"),
      cur_buffer_(new LogBuffer(kLogConfig.log_buffer_size)) {
  mkdir(basename_.c_str(), 0755);
  start();
}

AsyncFileAppender::~AsyncFileAppender() {
  if (started_) {
    stop();
  }
}

void AsyncFileAppender::append(const char *msg, size_t len) {
  MutexGuard guard(mutex_);

  if (cur_buffer_->available() >= len) {
    cur_buffer_->append(msg, len);
  } else {
    buffers_.push_back(std::move(cur_buffer_));

    cur_buffer_.reset(new LogBuffer(kLogConfig.log_buffer_size));
    cur_buffer_->append(msg, len);
    cond_.notifyOne();
  }
}

void AsyncFileAppender::start() {
  started_ = true;
  running_ = true;
  persit_thread_.start();
  countdown_latch_.wait();
}

void AsyncFileAppender::stop() {
  started_ = false;
  cond_.notifyOne();
  persit_thread_.join();
}

void AsyncFileAppender::threadFunc() {
  std::unique_ptr<LogBuffer> buffer(new LogBuffer(kLogConfig.log_buffer_size));
  std::vector<std::unique_ptr<LogBuffer>> persist_buffers;
  persist_buffers.reserve(kLogConfig.log_buffer_nums);
  LogFile log_file(basename_, kLogConfig.file_option.log_flush_file_size,
                   kLogConfig.file_option.log_flush_interval, 1024,
                   kLogConfig.file_option.file_writer_type);

  countdown_latch_.countDown();

  while (running_) {
    {
      MutexGuard gurd(mutex_);
      // wake up every persist_per_seconds_ or on Buffer is full
      if (buffers_.empty()) {
        cond_.waitForSeconds(persist_period_);
      }
      if (buffers_.empty() && cur_buffer_->length() == 0) {
        continue;
      }

      buffers_.push_back(std::move(cur_buffer_));

      // reset  cur_buffer_ and buffers_
      persist_buffers.swap(buffers_);
      cur_buffer_ = std::move(buffer);
      cur_buffer_->clear();
    }

    // if log is too large, drop it
    if (persist_buffers.size() > kLogConfig.log_buffer_size) {
      std::cerr << "log is too large, drop some" << std::endl;
      persist_buffers.erase(persist_buffers.begin() + 1, persist_buffers.end());
    }

    // persist log
    for (const auto &buffer : persist_buffers) {
      log_file.append(buffer->data(), buffer->length());
    }

    // reset buffer and persist_buffers
    buffer = std::move(persist_buffers[0]);
    buffer->clear();
    persist_buffers.clear();

    log_file.flush();

    if (!started_) {
      MutexGuard guard(mutex_);
      if (cur_buffer_->length() == 0) {
        running_ = false;
      }
    }
  }
  log_file.flush();
}

} // namespace naruto

} // namespace hardcode
