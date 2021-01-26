#ifndef NARUTO_INLCUDE_FILE_WRITER_H_
#define NARUTO_INLCUDE_FILE_WRITER_H_
#include <stdint.h>
namespace hardcode {
namespace naruto {
enum class FileWriterType : uint8_t { MMAPFILE = 0, APPENDFILE };
} // namespace naruto

} // namespace hardcode

#endif