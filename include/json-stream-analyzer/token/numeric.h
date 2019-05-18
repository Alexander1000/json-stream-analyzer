#ifndef TOKEN_NUMERIC_INCLUDED
#define TOKEN_NUMERIC_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

class TokenNumeric : public Token
{
public:
    TokenNumeric(int line, int column, IOReader* reader);
    int getType();
};

#endif
