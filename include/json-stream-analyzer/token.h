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

#include <json-stream-analyzer/token/braces-close.h>
#include <json-stream-analyzer/token/braces-open.h>
#include <json-stream-analyzer/token/comma.h>
#include <json-stream-analyzer/token/colon.h>
#include <json-stream-analyzer/token/quotes.h>
#include <json-stream-analyzer/token/text.h>
#include <json-stream-analyzer/token/numeric.h>

namespace JsonStreamAnalyzer::Token {
    class Token {
    public:
        Token(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader);

        int getLine();

        int getColumn();

        JsonStreamAnalyzer::Buffer::IOReader *getReader();

        virtual int getType() = 0;
    protected:
        int line;
        int column;
        JsonStreamAnalyzer::Buffer::IOReader *reader;
    };

    // --------------------------
    // --- Token: array close ---
    // --------------------------

    class TokenArrayClose : public Token {
    public:
        TokenArrayClose(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader);
        int getType();
    };

    // -------------------------
    // --- Token: array open ---
    // -------------------------

    class TokenArrayOpen : public Token {
    public:
        TokenArrayOpen(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader);
        int getType();
    };
}

#endif /* TOKEN_INCLUDED */
