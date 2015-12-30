#include "Debug.hpp"
#include <sstream>
#include <cstdarg>

INITIALIZE_EASYLOGGINGPP

namespace io
{

void Debug::ThrowException(const char *file, int line, const char *format, ...)
{
    char buffer[4096];
    va_list ap;
    va_start(ap, format);
    vsprintf_s(buffer, format, ap);
    va_end(ap);

    std::stringstream ss;
    ss << buffer << " (" << file << ":" << line << ")";
    throw std::runtime_error(ss.str());
}

}