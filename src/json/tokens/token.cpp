#include <json-stream-analyzer/io_buffer.h>

namespace JsonStreamAnalyzer {

    namespace Token {

        class Token {
        public:
            Token(int line, int column, IOReader *reader) {
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

            IOReader *getReader() {
                return this->reader;
            }

            virtual int getType() = 0;

        protected:
            int line;
            int column;
            IOReader *reader;
        };

    } // Token

} // JsonStreamAnalyzer
