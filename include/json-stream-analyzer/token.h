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

#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token {
    class Token {
    public:
        Token(int line, int column, IOBuffer::IOReader *reader);

        int getLine();

        int getColumn();

        IOBuffer::IOReader *getReader();

        virtual int getType() = 0;
    protected:
        int line;
        int column;
        IOBuffer::IOReader *reader;
    };

    // --------------------------
    // --- Token: array close ---
    // --------------------------

    class TokenArrayClose : public Token {
    public:
        TokenArrayClose(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };

    // -------------------------
    // --- Token: array open ---
    // -------------------------

    class TokenArrayOpen : public Token {
    public:
        TokenArrayOpen(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };

    // ---------------------------
    // --- Token: braces close ---
    // ---------------------------

    class TokenBracesClose : public Token {
    public:
        TokenBracesClose(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };

    // ---------------------------
    // --- Token: braces open ---
    // ---------------------------

    class TokenBracesOpen : public Token {
    public:
        TokenBracesOpen(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };

    // --------------------
    // --- Token: colon ---
    // --------------------

    class TokenColon : public Token {
    public:
        TokenColon(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };

    // --------------------
    // --- Token: comma ---
    // --------------------

    class TokenComma : public Token {
    public:
        TokenComma(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };

    // ----------------------
    // --- Token: numeric ---
    // ----------------------

    class TokenNumeric : public Token {
    public:
        TokenNumeric(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };

    // ---------------------
    // --- Token: quotes ---
    // ---------------------

    class TokenQuotes : public Token {
    public:
        TokenQuotes(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };

    // -------------------
    // --- Token: text ---
    // -------------------

    class TokenLexemeWord : public Token {
    public:
        TokenLexemeWord(int line, int column, IOBuffer::IOReader *reader);
        int getType();
    };
}

#endif /* TOKEN_INCLUDED */
