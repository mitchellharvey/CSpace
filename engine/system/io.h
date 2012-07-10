// File:        system/io.h
// Author:      Mitchell Harvey
// Date:        4/7/2012
// 

#ifndef ENGINE_SYSTEM_IO_H_
#define ENGINE_SYSTEM_IO_H_

#include "system/utf8.h"

namespace engine {
namespace system {

enum IORESULT
{
    IO_OK = 0,
    IO_NO_FILE_EXIST,
    IO_READ_ERROR,
    IO_WRITE_ERROR
};

IORESULT ReadFileText(const system::utf8 &filename, system::utf8 &output);

} // system
} // engine

#endif // ENGINE_SYSTEM_system::utf8_H_
