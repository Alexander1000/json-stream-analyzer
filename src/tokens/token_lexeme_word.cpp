#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenLexemeWord::TokenLexemeWord(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenLexemeWord::getType() {
        return TOKEN_TYPE_TEXT;
    }
} // JsonStreamAnalyzer::Token
