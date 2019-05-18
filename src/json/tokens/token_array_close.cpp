#include <json-stream-analyzer/token.h>

class TokenArrayClose : public Token
{
public:
    TokenArrayClose(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
    }

    int getType()
    {
        return TOKEN_TYPE_ARRAY_CLOSE;
    }
};
