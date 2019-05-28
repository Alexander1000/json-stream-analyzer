#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer::Token {

    Token::Token(int line, int column, IOBuffer::IOReader *reader) {
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

    IOBuffer::IOReader* Token::getReader() {
        return this->reader;
    }
} // JsonStreamAnalyzer::Token
