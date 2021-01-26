#ifndef KANGAROON_LOG_BUFFER_H_
#define KANGAROON_LOG_BUFFER_H_
#include <sys/types.h>
namespace zoo {
namespace kangaroo {

class LogBuffer {
   public:
    LogBuffer(size_t total = 1024 * 1024 * 10);
    ~LogBuffer();

    void clear();
    void append(const char* data, size_t len);
    const char* data() const;
    size_t length() const;
    size_t available() const;
    // for used by GDB
    const char* debugString();
    void setCookie(void (*cookie)()) { cookie_ = cookie; }

   private:
    char* data_;
    const size_t total_;
    size_t available_;
    size_t cur_;
    // Must be outline function for cookies.
    static void cookieStart();
    static void cookieEnd();

    void (*cookie_)();
};

}  // namespace kangaroo

}  // namespace zoo

#endif