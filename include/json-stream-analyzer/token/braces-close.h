#ifndef TOKEN_BRACES_CLOSE_INCLUDED
#define TOKEN_BRACES_CLOSE_INCLUDED

#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/io_buffer.h>

class TokenBracesClose : public Token
{
public:
    TokenBracesClose(int line, int column, IOReader* reader);
    int getType();
};

#endif
