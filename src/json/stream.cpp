#include <json-stream-analyzer/token.h>

#include <json-stream-analyzer/io_buffer.h>

#include <json-stream-analyzer/token/array-close.h>
#include <json-stream-analyzer/token/array-open.h>
#include <json-stream-analyzer/token/braces-close.h>
#include <json-stream-analyzer/token/braces-open.h>
#include <json-stream-analyzer/token/comma.h>
#include <json-stream-analyzer/token/colon.h>
#include <json-stream-analyzer/token/quotes.h>
#include <json-stream-analyzer/token/text.h>
#include <json-stream-analyzer/token/numeric.h>

#include <json-stream-analyzer/buffer/memory-buffer.h>

#include <string.h>
#include <memory>

#define STREAM_BUFFER_SIZE 4096

#define JSON_LEXER_PLAIN_MODE 0
#define JSON_LEXER_TEXT_MODE 1
#define JSON_LEXER_DIGIT_MODE 2
#define JSON_LEXER_WORD_MODE  3

namespace JsonStreamAnalyzer {

    class Stream {
    public:
        Stream(Buffer::IOReader *reader) {
            this->reader = reader;

            this->currentBuffer = new char[STREAM_BUFFER_SIZE];
            this->forwardBuffer = new char[STREAM_BUFFER_SIZE];

            ::std::memset(this->currentBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
            ::std::memset(this->forwardBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));

            this->currentPosition = 0;

            // признак того что достигнут конец файла
            this->eof = false;
            // позиция в буфере
            this->posCurrent = 0;
            this->posForward = 0;

            this->currentLine = 0;
            this->currentColumn = 0;

            this->mode = JSON_LEXER_PLAIN_MODE;
            this->prevMode = JSON_LEXER_PLAIN_MODE;

            this->lastFrame = false;
        }

        ~Stream() {
            delete this->currentBuffer;
            delete this->forwardBuffer;
        }

        Token::Token *get_next_token() {
            if (this->lastFrame && this->currentPosition == this->posCurrent) {
                // достигнут конец
                return NULL;
            }

            if (this->currentPosition == 0 && this->posCurrent == 0) {
                // первый раз тут, читаем данные
                // позиция в буфере
                this->posCurrent = this->reader->read(this->currentBuffer, STREAM_BUFFER_SIZE);
                this->posForward = 0;

                if (this->posCurrent < STREAM_BUFFER_SIZE) {
                    this->eof = true;
                    this->lastFrame = true;
                } else {
                    this->posForward = this->reader->read(this->forwardBuffer, STREAM_BUFFER_SIZE);
                    if (this->posForward < STREAM_BUFFER_SIZE) {
                        this->eof = true;
                    }
                }
            }

            bool endOfToken = false;
            this->lexemeWriter = NULL;
            bool escape = false;
            Token::Token *token = NULL;

            while (!endOfToken) {
                // если текущий указатель перешел в forward-буфер
                if (this->currentPosition >= STREAM_BUFFER_SIZE) {
                    // очищаем буфер со старыми данными
                    std::memset(this->currentBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
                    // копируем данные из forward buffer в current
                    std::memcpy(this->currentBuffer, this->forwardBuffer, STREAM_BUFFER_SIZE);
                    // копируем конечную позицию в буфере из forward в current
                    this->posCurrent = this->posForward;
                    // смещаем текущую позицию
                    this->currentPosition -= STREAM_BUFFER_SIZE;
                    // подготавливаем память для заливки новых данных
                    std::memset(this->forwardBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));

                    if (!this->eof) {
                        // если не был достигнут конец файла, читаем новый forward-буфер
                        this->posForward = this->reader->read(this->forwardBuffer, STREAM_BUFFER_SIZE);

                        if (this->posForward < STREAM_BUFFER_SIZE) {
                            this->eof = true;
                        }
                    } else {
                        // если конец файла, то освобождаем память от forward-буфера
                        this->posForward = 0;
                        this->lastFrame = true;
                    }
                }

                // текущий указатель находится внутри первого буфера
                bool move_position = true;
                // продвигаемся по буферу вперед
                char symbol = this->currentBuffer[this->currentPosition];

                switch (this->mode) {
                    case JSON_LEXER_PLAIN_MODE:
                        switch (symbol) {
                            case '{':
                                this->appendCurrentLexeme(symbol);
                                endOfToken = true;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                token = new Token::TokenBracesOpen(this->currentLine, this->currentColumn, this->lexemeWriter);
                                break;
                            case '}':
                                this->appendCurrentLexeme(symbol);
                                endOfToken = true;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                token = new Token::TokenBracesClose(this->currentLine, this->currentColumn,
                                                             this->lexemeWriter);
                                break;
                            case '[':
                                this->appendCurrentLexeme(symbol);
                                endOfToken = true;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                token = new Token::TokenArrayOpen(this->currentLine, this->currentColumn, this->lexemeWriter);
                                break;
                            case ']':
                                this->appendCurrentLexeme(symbol);
                                endOfToken = true;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                token = new Token::TokenArrayClose(this->currentLine, this->currentColumn, this->lexemeWriter);
                                break;
                            case ':':
                                this->appendCurrentLexeme(symbol);
                                endOfToken = true;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                token = new Token::TokenColon(this->currentLine, this->currentColumn, this->lexemeWriter);
                                break;
                            case ',':
                                this->appendCurrentLexeme(symbol);
                                endOfToken = true;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                token = new Token::TokenComma(this->currentLine, this->currentColumn, this->lexemeWriter);
                                break;
                            case '"':
                                this->appendCurrentLexeme(symbol);
                                endOfToken = true;
                                if (this->prevMode != JSON_LEXER_TEXT_MODE) {
                                    this->mode = JSON_LEXER_TEXT_MODE;
                                    escape = false;
                                }
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                token = new Token::TokenQuotes(this->currentLine, this->currentColumn, this->lexemeWriter);
                                break;
                        }

                        if (!endOfToken) {
                            if (symbol == ' ' || symbol == 0x0A || symbol == 0x0D) {
                                this->mode = JSON_LEXER_PLAIN_MODE;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                            } else if (this->is_digit(symbol)) {
                                this->mode = JSON_LEXER_DIGIT_MODE;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                move_position = false;
                            } else if (this->is_word(symbol)) {
                                this->mode = JSON_LEXER_WORD_MODE;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                                move_position = false;
                            } else {
                                this->mode = JSON_LEXER_PLAIN_MODE;
                                this->prevMode = JSON_LEXER_PLAIN_MODE;
                            }
                        }

                        break;
                    case JSON_LEXER_TEXT_MODE:
                        if (symbol == '\\' && !escape) {
                            escape = true;
                        } else {
                            if (symbol == '"' && !escape) {
                                move_position = false;
                                endOfToken = true;
                                this->mode = JSON_LEXER_PLAIN_MODE;
                                this->prevMode = JSON_LEXER_TEXT_MODE;
                                token = new Token::TokenLexemeWord(this->currentLine, this->currentColumn, this->lexemeWriter);
                            } else {
                                this->appendCurrentLexeme(symbol);
                            }
                            escape = false;
                        }
                        break;
                    case JSON_LEXER_DIGIT_MODE:
                        if (this->is_digit(symbol) || symbol == '.') {
                            this->appendCurrentLexeme(symbol);
                        } else {
                            endOfToken = true;
                            this->mode = this->prevMode;
                            this->prevMode = JSON_LEXER_DIGIT_MODE;
                            move_position = false;
                            token = new Token::TokenNumeric(this->currentLine, this->currentColumn, this->lexemeWriter);
                        }
                        break;
                    case JSON_LEXER_WORD_MODE:
                        if (!this->is_word(symbol)) {
                            endOfToken = true;
                            this->mode = this->prevMode;
                            this->prevMode = JSON_LEXER_WORD_MODE;
                            move_position = false;
                            token = new Token::TokenLexemeWord(this->currentLine, this->currentColumn, this->lexemeWriter);
                        } else {
                            this->appendCurrentLexeme(symbol);
                        }
                        break;
                }

                if (move_position) {
                    // координаты токена
                    if (symbol == 0x0A) {
                        this->currentColumn = 0;
                        ++this->currentLine;
                    } else {
                        ++this->currentColumn;
                    }

                    ++this->currentPosition;
                }

                if (this->lastFrame && this->currentPosition == this->posCurrent) {
                    break;
                }
            }

            return token;
        }

    private:
        Buffer::IOReader *reader;

        char *currentBuffer;
        char *forwardBuffer;

        // текущая позиция для чтения
        int currentPosition;

        // позиция начала текущего блока
        int posCurrent;
        // позиция начала следующего блока
        int posForward;

        // признак конца потока
        bool eof;

        // координаты токена в документе
        int currentLine;
        int currentColumn;

        Buffer::IOMemoryBuffer *lexemeWriter;

        int mode;
        int prevMode;

        bool lastFrame;

        bool is_digit(char symbol) {
            return symbol >= '0' && symbol <= '9';
        }

        bool is_word(char symbol) {
            return symbol >= 'a' && symbol <= 'z';
        }

        void appendCurrentLexeme(char symbol) {
            if (this->lexemeWriter == NULL) {
                this->lexemeWriter = new Buffer::IOMemoryBuffer;
            }

            this->lexemeWriter->write(&symbol, 1);
        }
    };

} // JsonStreamAnalyzer
