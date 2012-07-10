// File:        system/io.cpp
// Author:      Mitchell Harvey
// Date:        4/7/2012
// 

#include "system/types.h"
#include "system/io.h"

namespace {
    const engine::system::UINT32 _fileChunkSize = 1024 * 1024 * 4;  // 4 MB
    char _fileChunk[_fileChunkSize] = {0};
}

namespace engine {
namespace system {

IORESULT ReadFileText(const system::utf8 &filename, system::utf8 &output)
{
    IORESULT res = IO_OK;

    // TODO: Account for different file encodings

    FILE *file = fopen(filename.c_str(), "r");
    if (file)
    {
        output.clear();

        while(!feof(file))
        {
            size_t r = fread(_fileChunk, sizeof(char), _fileChunkSize, file);
            if (ferror(file))
            {
                //TODO: Log file read error
                fclose(file);
                return IO_READ_ERROR;
            }
            _fileChunk[r] = 0;
            output.append(_fileChunk);
        }

        fclose(file);
    }
    else
    {
        res = IO_NO_FILE_EXIST;
    }
    
    return res;
}

} // system
} // engine

