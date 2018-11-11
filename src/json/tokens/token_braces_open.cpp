class TokenBracesOpen : public Token
{
public:
    TokenBracesOpen(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
    }

    int getType()
    {
        return TOKEN_TYPE_BRACES_OPEN;
    }
};
