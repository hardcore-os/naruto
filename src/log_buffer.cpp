
#include "log_buffer.h"

#include <string.h>
namespace zoo {
namespace kangaroo {

LogBuffer::LogBuffer(size_t total) : total_(total), available_(total), cur_(0) {
    data_ = new char[total];
    setCookie(cookieStart);
}

LogBuffer::~LogBuffer() {
    delete[] data_;
    setCookie(cookieEnd);
}

size_t LogBuffer::available() const { return available_; }

void LogBuffer::clear() {
    cur_ = 0;
    available_ = total_;
}

void LogBuffer::append(const char* data, size_t len) {
    memcpy(data_ + cur_, data, len);
    cur_ += len;
    available_ -= len;
}

const char* LogBuffer::data() const { return data_; }

size_t LogBuffer::length() const { return cur_; }

void LogBuffer::cookieStart() {}

void LogBuffer::cookieEnd() {}
}  // namespace kangaroo

}  // namespace zoo
