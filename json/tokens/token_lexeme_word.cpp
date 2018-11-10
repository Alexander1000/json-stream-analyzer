class TokenLexemeWord : public Token
{
public:
    TokenLexemeWord(int line, int column, IOReader* reader) : Token(line, column)
    {
        this->reader = reader;
    }

protected:
    IOReader* reader;
};
