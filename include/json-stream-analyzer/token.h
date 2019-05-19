#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED

#define TOKEN_TYPE_TEXT 0
#define TOKEN_TYPE_BRACES_OPEN 1
#define TOKEN_TYPE_BRACES_CLOSE 2
#define TOKEN_TYPE_COMMA 3
#define TOKEN_TYPE_QUOTES 4
#define TOKEN_TYPE_COLON 5
#define TOKEN_TYPE_ARRAY_OPEN 6
#define TOKEN_TYPE_ARRAY_CLOSE 7
#define TOKEN_TYPE_NUMERIC 8

#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Token {

    class Token {
    public:
        Token(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader);

        int getLine();

        int getColumn();

        JsonStreamAnalyzer::Buffer::IOReader *getReader();

        virtual int getType() = 0;
    };

}

#endif /* TOKEN_INCLUDED */
