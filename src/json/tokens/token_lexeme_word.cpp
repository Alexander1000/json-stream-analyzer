#include <json-stream-analyzer/token.h>

class TokenLexemeWord : public Token
{
public:
    TokenLexemeWord(int line, int column, IOReader* reader) : Token(line, column, reader)
    {
    }

    int getType()
    {
        return TOKEN_TYPE_TEXT;
    }
};
