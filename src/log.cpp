#include "log.h"

#include <stdarg.h>
#include <string.h>

#include <algorithm>
#include <string>
#include <vector>

#include "log_level.h"
#include "time_stamp.h"

namespace zoo {
namespace kangaroo {
namespace {
std::string getLogLevelStr(LogLevel log_level) {
    switch (log_level) {
#define XX(name)         \
    case LogLevel::name: \
        return #name;    \
        break;

        XX(DEBUG);
        XX(INFO);
        XX(WARN);
        XX(ERROR);
        XX(FATAL);
#undef XX
        default:
            return "UNKNOW";
    }
    return "UNKNOW";
}
}  // namespace

void Logger::info(const char *format, ...) {
    if (!format) {
        return;
    }
    va_list ap;

    va_start(ap, format);
    writeLog(LogLevel::INFO, __FILE__, __FUNCTION__, __LINE__, format, ap);
    va_end(ap);
}
void Logger::debug(const char *format, ...) {
    if (!format) {
        return;
    }
    va_list ap;

    va_start(ap, format);
    writeLog(LogLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, format, ap);
    va_end(ap);
}
void Logger::warn(const char *format, ...) {
    if (!format) {
        return;
    }
    va_list ap;

    va_start(ap, format);
    writeLog(LogLevel::WARN, __FILE__, __FUNCTION__, __LINE__, format, ap);
    va_end(ap);
}
void Logger::error(const char *format, ...) {
    if (!format) {
        return;
    }
    va_list ap;

    va_start(ap, format);
    writeLog(LogLevel::ERROR, __FILE__, __FUNCTION__, __LINE__, format, ap);
    va_end(ap);
}
void Logger::fatal(const char *format, ...) {
    if (!format) {
        return;
    }
    va_list ap;

    va_start(ap, format);
    writeLog(LogLevel::FATAL, __FILE__, __FUNCTION__, __LINE__, format, ap);
    va_end(ap);
}
/*需要加锁的*/
void Logger::addAppender(const std::string &appender_name,
                         LogAppenderInterface::Ptr appender) {
    MutexGuard guard(mutex_);
    appenders_[appender_name] = appender;
}
void Logger::delAppender(const std::string &appender_name) {
    MutexGuard guard(mutex_);
    for(auto it = appenders_.begin(); it != appenders_.end(); ) {
        if (it->first == appender_name) {
            it = appenders_.erase(it);
        } else {
            ++it;
        }
            
    }
}
void Logger::clearAppender() { appenders_.clear(); }

void Logger::writeLog(LogLevel log_level, const char *file_name,
                      const char *function_name, int32_t line_num,
                      const char *fmt, va_list ap) {
    if (log_level < kLogConfig.log_level) {
        return;
    }
    std::string str_result;
    if (nullptr != fmt) {
        size_t length = vprintf(fmt, ap) + 1;  //获取格式化字符串长度
        std::vector<char> fmt_bufs(length,
                                   '\0');  //创建用于存储格式化字符串的字符数组
        int writen_n = vsnprintf(&fmt_bufs[0], fmt_bufs.size(), fmt, ap);
        if (writen_n > 0) {
            str_result = &fmt_bufs[0];
        }
    }
    if (str_result.empty()) {
        return;
    }
    const auto &getSourceFileName = [](const char *file_name) {
        return strrchr(file_name, '/') ? strrchr(file_name, '/') + 1
                                       : file_name;
    };
    std::string prefix;
    prefix.append(Timestamp::nowStrTime() + "-");
    prefix.append(getLogLevelStr(log_level) + "-");
    prefix.append(getSourceFileName(file_name));
    prefix.append("-");
    prefix.append(function_name);
    prefix.append("-");
    prefix.append(std::to_string(line_num) + "-");
    prefix.append(str_result);
    MutexGuard guard(mutex_);
    for (const auto &appender : appenders_) {
        appender.second->append(prefix.data(), prefix.size());
    }
}
}  // namespace kangaroo

}  // namespace zoo