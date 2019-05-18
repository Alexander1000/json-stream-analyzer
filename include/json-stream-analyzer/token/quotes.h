#ifndef TOKEN_QUOTES_INCLUDED
#define TOKEN_QUOTES_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

class TokenQuotes : public Token
{
public:
    TokenQuotes(int line, int column, IOReader* reader);
    int getType();
};

#endif
