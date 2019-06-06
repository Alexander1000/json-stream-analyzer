#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/stream.h>
#include <io-buffer.h>

#include <memory.h>

#define STREAM_BUFFER_SIZE 4096

#define JSON_LEXER_PLAIN_MODE 0
#define JSON_LEXER_TEXT_MODE 1
#define JSON_LEXER_DIGIT_MODE 2
#define JSON_LEXER_WORD_MODE  3

namespace JsonStreamAnalyzer
{
    Stream::Stream(IOBuffer::IOReader *reader) {
        this->reader = reader;

        this->currentBuffer = new char[STREAM_BUFFER_SIZE];
        this->forwardBuffer = new char[STREAM_BUFFER_SIZE];

        memset(this->currentBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
        memset(this->forwardBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));

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

    Stream::~Stream() {
        delete this->currentBuffer;
        delete this->forwardBuffer;
    }

    Token::Token* Stream::get_next_token()
    {
        bool endOfToken = false;
        this->lexemeWriter = NULL;
        bool escape = false;
        Token::Token *token = NULL;

        char* curChar = this->getNextChar();

        while (!endOfToken && curChar != NULL) {
            // текущий указатель находится внутри первого буфера
            bool move_position = true;

            char symbol = *curChar;

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
                            this->appendCurrentLexeme('\00');
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
                        this->appendCurrentLexeme('\00');
                        token = new Token::TokenNumeric(this->currentLine, this->currentColumn, this->lexemeWriter);
                    }
                    break;
                case JSON_LEXER_WORD_MODE:
                    if (!this->is_word(symbol)) {
                        endOfToken = true;
                        this->appendCurrentLexeme('\00');

                        if (this->prevMode == JSON_LEXER_PLAIN_MODE) {
                            int length = this->lexemeWriter->length();
                            // literal: (true|null) + \x00
                            if (length == 5) {
                                // check true
                                char* tb = (char*) malloc(sizeof(char) * 5);
                                memset(tb, 0, sizeof(char) * 5);
                                this->lexemeWriter->read(tb, 4);
                                std::string sTrue = "true";
                                std::string sNull = "null";
                                if (sTrue == tb) {
                                    token = new Token::TokenBool(
                                        this->currentLine,
                                        this->currentColumn,
                                        true
                                    );
                                } else if (sNull == tb) {
                                    token = new Token::TokenNull(
                                        this->currentLine,
                                        this->currentColumn
                                    );
                                }
                                free(tb);
                            } else if (length == 6) {
                                // check false
                                // strlen("false") + \x00
                                char* tb = (char*) malloc(sizeof(char) * 6);
                                memset(tb, 0, sizeof(char) * 6);
                                this->lexemeWriter->read(tb, 5);
                                std::string sFalse = "false";
                                if (sFalse == tb) {
                                    token = new Token::TokenBool(
                                        this->currentLine,
                                        this->currentColumn,
                                        false
                                    );
                                }
                                free(tb);
                            }
                        }

                        this->mode = this->prevMode;
                        this->prevMode = JSON_LEXER_WORD_MODE;
                        move_position = false;

                        if (token == NULL) {
                            token = new Token::TokenLexemeWord(
                                this->currentLine,
                                this->currentColumn,
                                this->lexemeWriter
                            );
                        }
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

            curChar = this->getNextChar();
        }

        return token;
    }

    char* Stream::getNextChar() {
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

        // если текущий указатель перешел в forward-буфер
        if (this->currentPosition >= STREAM_BUFFER_SIZE) {
            // очищаем буфер со старыми данными
            memset(this->currentBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
            // копируем данные из forward buffer в current
            memcpy(this->currentBuffer, this->forwardBuffer, STREAM_BUFFER_SIZE);
            // копируем конечную позицию в буфере из forward в current
            this->posCurrent = this->posForward;
            // смещаем текущую позицию
            this->currentPosition -= STREAM_BUFFER_SIZE;
            // подготавливаем память для заливки новых данных
            memset(this->forwardBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));

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

        return &this->currentBuffer[this->currentPosition];
    }
} // JsonStreamAnalyzer
