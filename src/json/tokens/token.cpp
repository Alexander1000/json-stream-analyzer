class Token
{
public:
    Token(int line, int column, IOReader* reader)
    {
        this->line = line;
        this->column = column;
        this->reader = reader;
    }

    int getLine()
    {
        return this->line;
    }

    int getColumn()
    {
        return this->column;
    }

    IOReader* getReader()
    {
        return this->reader;
    }

protected:
    int line;
    int column;
    IOReader* reader;
};
