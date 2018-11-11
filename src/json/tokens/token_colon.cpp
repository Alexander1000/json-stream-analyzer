class TokenColon : public Token
{
public:
    TokenColon(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
    }

    int getType()
    {
        return TOKEN_TYPE_COLON;
    }
};
