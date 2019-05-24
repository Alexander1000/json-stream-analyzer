#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{
    TokenLexemeWord::TokenLexemeWord(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int TokenLexemeWord::getType() {
        return TOKEN_TYPE_TEXT;
    }
} // JsonStreamAnalyzer::Token
