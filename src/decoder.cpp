#include <map>
#include <string>
#include <list>
#include <iostream>
#include <memory.h>

#include <json-stream-analyzer/element.h>
#include <json-stream-analyzer/stream.h>
#include <json-stream-analyzer/token.h>
#include <json-stream-analyzer/decoder.h>

namespace JsonStreamAnalyzer {

    Decoder::Decoder(Stream *stream) {
        this->stream = stream;
    }

    Element* Decoder::decode() {
        return this->parse();
    }

    Element* Decoder::parse() {
        return this->parse_element();
    }

    Element* Decoder::parse_element() {
        return this->parse_element(this->stream->get_next_token());
    }

    Element* Decoder::parse_element(Token::Token *token) {
        if (token == NULL) {
            return NULL;
        }

        Element* element;
        std::map<std::string, Element *> *obj;
        std::string *text;
        std::string *digit;
        std::list<Element *> *array;

        switch (token->getType()) {
            case Token::Type::BracesOpen:
                // object
                obj = this->parse_object();
                element = new Element(ELEMENT_TYPE_OBJECT, (void*) obj);
                break;
            case Token::Type::Quotes:
                // text
                text = this->parse_text();
                element = new Element(ELEMENT_TYPE_TEXT, (void*) text);
                break;
            case Token::Type::Numeric:
                // numeric
                digit = this->parse_numeric(token);
                element = new Element(ELEMENT_TYPE_NUMERIC, (void*) digit);
                break;
            case Token::Type::ArrayOpen:
                // array
                array = this->parse_array();
                element = new Element(ELEMENT_TYPE_ARRAY, (void*) array);
                break;
            case Token::Type::Bool:
                element = new Element(ELEMENT_TYPE_BOOL, (void*) ((JsonStreamAnalyzer::Token::TokenBool*) token)->getValue());
                break;
            case Token::Type::Null:
                element = new Element(ELEMENT_TYPE_NULL, NULL);
                break;
            default:
                throw new UnexpectedTokenException(token);
        }

        return element;
    }

    std::map<std::string, Element *>* Decoder::parse_object() {
        std::map<std::string, Element *> *object;
        object = new std::map<std::string, Element *>;

        Token::Token *token;

        bool isFirstElement = true;

        PARSE_OBJ_PROPERTY:
        token = this->stream->get_next_token();
        if (isFirstElement && token->getType() == Token::Type::BracesClose) {
            // empty object
            return object;
        }

        if (token->getType() != Token::Type::Quotes) {
            // unexpected, object property must be have quote
            throw new UnexpectedTokenException(token);
        }

        token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Text) {
            throw new UnexpectedTokenException(token);
        }

        // @todo: optimize and reuse (memory managment)
        char *property_name = (char *) malloc(sizeof(char) * 1024);
        memset(property_name, 0, sizeof(char) * 1024);
        token->getReader()->read(property_name, 1024);

        token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Quotes) {
            throw new UnexpectedTokenException(token);
        }

        token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Colon) {
            throw new UnexpectedTokenException(token);
        }

        Element *property_value = this->parse_element();

        (*object)[std::string(property_name)] = property_value;

        token = this->stream->get_next_token();

        switch (token->getType()) {
            case Token::Type::Comma:
                // parse next object property key-val
                // todo: fixme, refactor
                isFirstElement = false;
                goto PARSE_OBJ_PROPERTY;
            case Token::Type::BracesClose:
                break;
            default:
                throw new UnexpectedTokenException(token);
        }

        // todo: allocate memory
        return object;
    }

    std::string* Decoder::parse_text() {
        Token::Token *token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Text) {
            throw new UnexpectedTokenException(token);
        }

        std::string *val;
        if (token->getReader() == NULL) {
            // empty token
            val = new std::string("");
        } else {
            char *text = (char *) malloc(sizeof(char) * 1024);
            memset(text, 0, sizeof(char) * 1024);
            token->getReader()->read(text, 1024);
            val = new std::string(text);
        }

        token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Quotes) {
            throw new UnexpectedTokenException(token);
        }

        return val;
    }

    std::string* Decoder::parse_numeric(Token::Token *token) {
        char *text = (char *) malloc(sizeof(char *) * 1024);
        memset(text, 0, sizeof(char) * 1024);
        token->getReader()->read(text, 1024);
        std::string *val = new std::string(text);
        return val;
    }

    std::list<Element *>* Decoder::parse_array() {
        std::list<Element *> *list;
        list = new std::list<Element *>;
        Element *element;

        bool isFirst = true;
        Token::Token *token = this->stream->get_next_token();

        if (token->getType() == Token::Type::ArrayClose) {
            return list;
        }

        PARSE_ARRAY:

        if (isFirst) {
            element = this->parse_element(token);
            isFirst = false;
        } else {
            element = this->parse_element();
        }

        list->push_back(element);

        token = this->stream->get_next_token();
        if (token->getType() == Token::Type::Comma) {
            // repeat
            goto PARSE_ARRAY;
        }

        if (token->getType() != Token::Type::ArrayClose) {
            throw new UnexpectedTokenException(token);
        }

        return list;
    }
} // JsonStreamAnalyzer
