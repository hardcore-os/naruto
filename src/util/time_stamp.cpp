#include "time_stamp.h"

#include <time.h>

#include <iostream>
namespace zoo{

namespace kangaroo{
Timestamp Timestamp::now() {
    struct timeval tv;
    if (gettimeofday(&tv, nullptr)) {
        return Timestamp();
    }
    return Timestamp(tv.tv_sec * kMicrosecondsPerSecond + tv.tv_usec);
}

time_t Timestamp::getSec() const {
    return microseconds_from_epoch_ / kMicrosecondsPerSecond;
}

suseconds_t Timestamp::getUsec() const {
    return microseconds_from_epoch_ % kMicrosecondsPerSecond;
}
std::string Timestamp::nowStrTime() {
    time_t timep;
    time(&timep);
    char res[64];
    strftime(res, sizeof(res), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return res;
}
}  // namespace

}  // namespace