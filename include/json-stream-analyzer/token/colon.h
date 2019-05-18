#ifndef TOKEN_COLON_INCLUDED
#define TOKEN_COLON_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

class TokenColon : public Token
{
public:
    TokenColon(int line, int column, IOReader* reader);
    int getType();
};

#endif
