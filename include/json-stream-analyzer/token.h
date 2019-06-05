#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED

#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token {
    enum Type {
        ArrayClose,
        ArrayOpen,
        BracesClose,
        BracesOpen,
        Colon,
        Comma,
        Numeric,
        Quotes,
        Text,
    };

    const char* getTokenTypeName(Type);

    class Token {
    public:
        Token(int line, int column, IOBuffer::IOReader *reader);

        int getLine();

        int getColumn();

        IOBuffer::IOReader *getReader();

        virtual Type getType() = 0;
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
        Type getType();
    };

    // -------------------------
    // --- Token: array open ---
    // -------------------------

    class TokenArrayOpen : public Token {
    public:
        TokenArrayOpen(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };

    // ---------------------------
    // --- Token: braces close ---
    // ---------------------------

    class TokenBracesClose : public Token {
    public:
        TokenBracesClose(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };

    // ---------------------------
    // --- Token: braces open ---
    // ---------------------------

    class TokenBracesOpen : public Token {
    public:
        TokenBracesOpen(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };

    // --------------------
    // --- Token: colon ---
    // --------------------

    class TokenColon : public Token {
    public:
        TokenColon(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };

    // --------------------
    // --- Token: comma ---
    // --------------------

    class TokenComma : public Token {
    public:
        TokenComma(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };

    // ----------------------
    // --- Token: numeric ---
    // ----------------------

    class TokenNumeric : public Token {
    public:
        TokenNumeric(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };

    // ---------------------
    // --- Token: quotes ---
    // ---------------------

    class TokenQuotes : public Token {
    public:
        TokenQuotes(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };

    // -------------------
    // --- Token: text ---
    // -------------------

    class TokenLexemeWord : public Token {
    public:
        TokenLexemeWord(int line, int column, IOBuffer::IOReader *reader);
        Type getType();
    };
}

#endif /* TOKEN_INCLUDED */
