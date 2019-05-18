#ifndef IO_BUFFER_FILE_INCLUDED
#define IO_BUFFER_FILE_INCLUDED

class IOFileReader : public IOReader
{
public:
    IOFileReader(char* fileName);
    int read(char* buffer, int length);
};

#endif
