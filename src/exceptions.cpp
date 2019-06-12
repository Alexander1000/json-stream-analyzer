#include <string>

#include <json-stream-analyzer/decoder.h>
#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer
{
    UnexpectedTokenException::UnexpectedTokenException(JsonStreamAnalyzer::Token::Token *token) {
        this->token = token;
    }

    char* UnexpectedTokenException::getMessage()
    {
        char* message = (char*) malloc(sizeof(char) * 45);
        sprintf(
            message,
            "unexpected token '%s' in %d:%d",
            Token::getTokenTypeName(this->token->getType()),
            token->getLine(),
            token->getColumn()
        );
        return message;
    }
}
