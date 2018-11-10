class Token
{
public:
    Token(int line, int column)
    {
        this->line = line;
        this->column = column;
    }

protected:
    int line;
    int column;
};
