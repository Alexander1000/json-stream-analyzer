#include <json-stream-analyzer/token.h>

class TokenNumeric : public Token
{
public:
    TokenNumeric(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
    }

    int getType()
    {
        return TOKEN_TYPE_NUMERIC;
    }
};
