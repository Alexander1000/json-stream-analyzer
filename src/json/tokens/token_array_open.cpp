#include <json-stream-analyzer/token.h>

class TokenArrayOpen : public Token
{
public:
    TokenArrayOpen(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
    }

    int getType()
    {
        return TOKEN_TYPE_ARRAY_OPEN;
    }
};
