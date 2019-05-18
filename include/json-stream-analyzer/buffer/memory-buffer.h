#ifndef IO_BUFFER_MEMORY_INCLUDED
#define IO_BUFFER_MEMORY_INCLUDED

class IOMemoryBuffer : public IOBuffer
{
public:
    int write(char *buffer, int length);
    int read(char *buffer, int length);
    void setPosition(int position);
    int length();
};

#endif
