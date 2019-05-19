#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token {
    class TokenBracesOpen : public Token {
    public:
        TokenBracesOpen(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
        }

        int getType() {
            return TOKEN_TYPE_BRACES_OPEN;
        }
    };
} // JsonStreamAnalyzer::Token