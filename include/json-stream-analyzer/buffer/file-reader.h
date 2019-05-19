#ifndef IO_BUFFER_FILE_INCLUDED
#define IO_BUFFER_FILE_INCLUDED

#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Buffer {
    class IOFileReader : public IOReader {
    public:
        IOFileReader(char *fileName);
        int read(char *buffer, int length);
    };
}

#endif
