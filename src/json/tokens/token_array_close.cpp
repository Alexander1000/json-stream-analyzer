#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token
{

class TokenArrayClose : public Token {
public:
    TokenArrayClose(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) : Token(line, column, reader) {
    }

    int getType() {
        return TOKEN_TYPE_ARRAY_CLOSE;
    }
};

} // JsonStreamAnalyzer::Token
