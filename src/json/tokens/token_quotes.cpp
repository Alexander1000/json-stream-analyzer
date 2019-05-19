#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token {
    class TokenQuotes : public Token {
    public:
        TokenQuotes(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
        }

        int getType() {
            return TOKEN_TYPE_QUOTES;
        }
    };
} // JsonStreamAnalyzer::Token