#ifndef DECODER_INCLUDED
#define DECODER_INCLUDED

#include <map>
#include <string>
#include <list>

#include <json-stream-analyzer/element.h>
#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/stream.h>

namespace JsonStreamAnalyzer
{
    class UnexpectedTokenException
    {
    public:
        UnexpectedTokenException(Token::Token* token);
        char* getMessage();
    private:
        Token::Token* token;
    };

    class Decoder {
    public:
        Decoder(Stream *stream);
        Element *decode();

    private:
        Stream *stream;
        Element* parse();
        Element* parse_element();
        Element* parse_element(Token::Token *token);
        std::map<std::string, Element*>* parse_object();
        std::string* parse_text();
        std::string* parse_numeric(Token::Token* token);
        std::list<Element*>* parse_array();
    };
}

#endif /* DECODER_INCLUDED */
