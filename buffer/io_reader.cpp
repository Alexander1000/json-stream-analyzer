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
