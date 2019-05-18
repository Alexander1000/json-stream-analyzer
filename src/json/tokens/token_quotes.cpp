#include <json-stream-analyzer/token.h>

class TokenQuotes : public Token
{
public:
    TokenQuotes(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
    }

    int getType()
    {
        return TOKEN_TYPE_QUOTES;
    }
};
