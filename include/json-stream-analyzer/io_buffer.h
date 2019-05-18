#ifndef IOBUFFER_INCLUDED
#define IOBUFFER_INCLUDED

#define IO_MEMORY_BLOCK_SIZE 512

class IOWriter
{
public:
    /**
     * Запись в IO length байт
     * @param char*
     * @param length
     * @return int количество записанных данных
     */
    virtual int write(char* buffer, int length) = 0;
};

class IOReader
{
public:
    /**
     * Чтение из IO length байт
     * @param char*
     * @param length
     * @return int количество прочитанных данных
     */
    virtual int read(char* buffer, int length) = 0;
};

class IOMemoryBuffer
{
public:
    int write(char *buffer, int length);
    int read(char *buffer, int length);
    void setPosition(int position);
    int length();
};

class IOFileReader
{
public:
    int read(char* buffer, int length);
};

#endif /* IOBUFFER_INCLUDED */