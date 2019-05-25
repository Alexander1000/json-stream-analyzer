#include <stdio.h>
#include <vector>

#ifndef IOBUFFER_INCLUDED
#define IOBUFFER_INCLUDED

namespace JsonStreamAnalyzer::Buffer {
    class IOWriter {
    public:
        virtual int write(char *buffer, int length) = 0;
    };

    class IOReader {
    public:
        virtual int read(char *buffer, int length) = 0;
    };

    class IOBuffer : public IOReader, public IOWriter {
    };

    class IOFileReader : public IOReader {
    public:
        IOFileReader(char *fileName);
        ~IOFileReader();
        int read(char *buffer, int length);
    private:
        char *fileName;
        FILE *hFile;
        FILE *getHandler();
    };

    class IOMemoryBuffer : public IOBuffer {
    public:
        IOMemoryBuffer();
        IOMemoryBuffer(int ioMemoryBlockSize);
        ~IOMemoryBuffer();
        int write(char *buffer, int length);
        int read(char *buffer, int length);
        void setPosition(int position);
        int length();
    protected:
        std::vector<char *> blocks;
        int ioMemoryBlockSize;
        int currentBlockNumber;
        int writePosition;
        int readPosition;
    };

} // JsonStreamAnalyzer::Buffer

#endif /* IOBUFFER_INCLUDED */
