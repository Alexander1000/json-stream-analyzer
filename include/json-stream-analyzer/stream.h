#ifndef JSON_STREAM_INCLUDED
#define JSON_STREAM_INCLUDED

#define STREAM_BUFFER_SIZE 4096

#define JSON_LEXER_PLAIN_MODE 0
#define JSON_LEXER_TEXT_MODE 1
#define JSON_LEXER_DIGIT_MODE 2
#define JSON_LEXER_WORD_MODE  3

#include <json-stream-analyzer/token.h>
#include <io-buffer.h>

namespace JsonStreamAnalyzer
{
    class Stream {
    public:
        Stream(IOBuffer::CharStream *charStream);
        Token::Token *get_next_token();
    private:
        IOBuffer::CharStream *charStream;

        // координаты токена в документе
        int currentLine;
        int currentColumn;

        IOBuffer::IOMemoryBuffer *lexemeWriter;

        int mode;
        int prevMode;

        bool is_digit(char symbol) {
            return symbol >= '0' && symbol <= '9';
        }

        bool is_word(char symbol) {
            return symbol >= 'a' && symbol <= 'z';
        }

        void appendCurrentLexeme(char symbol) {
            if (this->lexemeWriter == NULL) {
                this->lexemeWriter = new IOBuffer::IOMemoryBuffer;
            }

            this->lexemeWriter->write(&symbol, 1);
        }
    };
}

#endif /* JSON_STREAM_INCLUDED */
