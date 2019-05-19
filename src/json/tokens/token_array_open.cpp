#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token {
    class TokenArrayOpen : public Token {
    public:
        TokenArrayOpen(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
        }

        int getType() {
            return TOKEN_TYPE_ARRAY_OPEN;
        }
    };
} // JsonStreamAnalyzer::Token