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


class IOBuffer : public IOReader, public IOWriter
{
public:
    IOBuffer() : IOReader(), IOWriter()
    {
    }
};
