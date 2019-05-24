#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer::Token {

    Token::Token(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) {
        this->line = line;
        this->column = column;
        this->reader = reader;
    }

    int Token::getLine() {
        return this->line;
    }

    int Token::getColumn() {
        return this->column;
    }

    JsonStreamAnalyzer::Buffer::IOReader* Token::getReader() {
        return this->reader;
    }
} // JsonStreamAnalyzer::Token
