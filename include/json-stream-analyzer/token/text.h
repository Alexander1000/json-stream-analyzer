#ifndef TOKEN_TEXT_INCLUDED
#define TOKEN_TEXT_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

class TokenLexemeWord : public Token
{
public:
    TokenLexemeWord(int line, int column, IOReader* reader);
    int getType();
};

#endif
