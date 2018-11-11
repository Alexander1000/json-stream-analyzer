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
