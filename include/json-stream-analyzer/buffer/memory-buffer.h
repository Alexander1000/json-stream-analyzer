#ifndef IO_BUFFER_MEMORY_INCLUDED
#define IO_BUFFER_MEMORY_INCLUDED

#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Buffer {
    class IOMemoryBuffer : public IOBuffer {
    public:
        IOMemoryBuffer();
        IOMemoryBuffer(int ioMemoryBlockSize);
        int write(char *buffer, int length);
        int read(char *buffer, int length);
        void setPosition(int position);
        int length();
    };
}

#endif
