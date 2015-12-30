#pragma once

#include <easylogging++.h>
#include <cassert>

namespace io
{

class Debug
{
public:
    static void ThrowException(const char *file, int line, const char *format, ...);
};

}

// Throws an exception with included file and line information.
#define Throw(...) (io::Debug::ThrowException(__FILE__, __LINE__, __VA_ARGS__))

// Assert that logs the assertion as well.
#define Assert(cond) do { if (!(cond)) { LOG(ERROR) << "Assert failed: " << #cond << " (" << __FILE__ << ":" << __LINE__ << ")"; } assert((cond)); } while(false)
