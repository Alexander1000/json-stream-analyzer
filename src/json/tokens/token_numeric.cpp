#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token {
    class TokenNumeric : public Token {
    public:
        TokenNumeric(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
        }

        int getType() {
            return TOKEN_TYPE_NUMERIC;
        }
    };

} // JsonStreamAnalyzer::Token
