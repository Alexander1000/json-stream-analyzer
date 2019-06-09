#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/stream.h>
#include <io-buffer.h>

#include <memory.h>

#define JSON_LEXER_PLAIN_MODE 0
#define JSON_LEXER_TEXT_MODE 1
#define JSON_LEXER_DIGIT_MODE 2
#define JSON_LEXER_WORD_MODE  3

namespace JsonStreamAnalyzer
{
    Stream::Stream(IOBuffer::CharStream *charStream) {
        this->charStream = charStream;

        this->currentLine = 0;
        this->currentColumn = 0;

        this->mode = JSON_LEXER_PLAIN_MODE;
        this->prevMode = JSON_LEXER_PLAIN_MODE;
    }

    Token::Token* Stream::get_next_token()
    {
        bool endOfToken = false;
        this->lexemeWriter = NULL;
        bool escape = false;
        Token::Token *token = NULL;

        char* curChar = this->charStream->getNext();

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
            }

            curChar = this->charStream->getNext();
        }

        return token;
    }
} // JsonStreamAnalyzer
