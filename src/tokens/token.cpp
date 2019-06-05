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

    const char* getTokenTypeName(Type type) {
        switch (type) {
            case ArrayClose:
                return "array.close";
            case ArrayOpen:
                return "array.open";
            case BracesClose:
                return "braces.close";
            case BracesOpen:
                return "braces.open";
            case Colon:
                return "colon";
            case Comma:
                return "comma";
            case Quotes:
                return "quotes";
            case Text:
                return "text";
            case Numeric:
                return "numeric";
            case Bool:
                return "bool";
            case Null:
                return "null";
        }
    }

} // JsonStreamAnalyzer::Token
