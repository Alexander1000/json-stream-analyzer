class TokenBracesClose : public Token
{
public:
    TokenBracesClose(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
    }

    int getType()
    {
        return TOKEN_TYPE_BRACES_CLOSE;
    }
};
