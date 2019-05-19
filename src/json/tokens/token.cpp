#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer::Token {

    class Token {
    public:
        Token(int line, int column, JsonStreamAnalyzer::Buffer::IOReader *reader) {
            this->line = line;
            this->column = column;
            this->reader = reader;
        }

        int getLine() {
            return this->line;
        }

        int getColumn() {
            return this->column;
        }

        JsonStreamAnalyzer::Buffer::IOReader *getReader() {
            return this->reader;
        }

        virtual int getType() = 0;

    protected:
        int line;
        int column;
        JsonStreamAnalyzer::Buffer::IOReader *reader;
    };

} // JsonStreamAnalyzer::Token
