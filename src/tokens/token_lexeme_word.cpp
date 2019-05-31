#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token
{
    TokenLexemeWord::TokenLexemeWord(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TokenLexemeWord::getType() {
        return Type::Text;
    }
} // JsonStreamAnalyzer::Token
