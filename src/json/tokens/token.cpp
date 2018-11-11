class Token
{
public:
    Token(int line, int column)
    {
        this->line = line;
        this->column = column;
    }

    int getLine()
    {
        return this->line;
    }

    int getColumn()
    {
        return this->column;
    }

protected:
    int line;
    int column;
};
