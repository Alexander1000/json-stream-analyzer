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
        Token::Token *token = this->stream->get_next_token();
        if (token == NULL) {
            return NULL;
        }

        Element *element;
        std::map<std::string, Element *> *obj;
        std::string *text;
        std::string *digit;
        std::list<Element *> *array;

        switch (token->getType()) {
            case Token::Type::BracesOpen:
                // object
                obj = this->parse_object();
                element = new Element(ELEMENT_TYPE_OBJECT, (void *) obj);
                return element;
            case Token::Type::Quotes:
                // text
                text = this->parse_text();
                element = new Element(ELEMENT_TYPE_TEXT, (void *) text);
                return element;
            case Token::Type::Numeric:
                // numeric
                digit = this->parse_numeric(token);
                element = new Element(ELEMENT_TYPE_NUMERIC, (void *) digit);
                return element;
            case Token::Type::ArrayOpen:
                // array
                array = this->parse_array();
                element = new Element(ELEMENT_TYPE_ARRAY, (void *) array);
                return element;
            case Token::Type::Bool:
                element = new Element(ELEMENT_TYPE_BOOL, (void*) ((JsonStreamAnalyzer::Token::TokenBool*) token)->getValue());
                return element;
            case Token::Type::Null:
                // todo: implement me
                return NULL;
            default:
                std::cout << "unexpected token: " << JsonStreamAnalyzer::Token::getTokenTypeName(token->getType()) << std::endl;
                if (token->getType() == Token::Type::Text) {
                    char *tokenValue = (char *) malloc(sizeof(char) * 1024);
                    memset(tokenValue, 0, sizeof(char) * 1024);
                    token->getReader()->read(tokenValue, 1024);
                    std::cout << "Text: " << tokenValue << std::endl;
                }
                // unsupporeted
                return NULL;
        }

        return NULL;
    }

    std::map<std::string, Element *>* Decoder::parse_object() {
        std::map<std::string, Element *> *object;
        object = new std::map<std::string, Element *>;

        Token::Token *token;

        PARSE_OBJ_PROPERTY:
        token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Quotes) {
            // unexpected, object property must be have quote
            // @todo: throw exception
            return NULL;
        }

        token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Text) {
            // unexpected
            // @todo: throw exception
            return NULL;
        }

        // @todo: optimize and reuse (memory managment)
        char *property_name = (char *) malloc(sizeof(char) * 1024);
        memset(property_name, 0, sizeof(char) * 1024);
        token->getReader()->read(property_name, 1024);

        token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Quotes) {
            // @todo: throw exception
            return NULL;
        }

        token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Colon) {
            // @todo: unexpected
            return NULL;
        }

        Element *property_value = this->parse_element();

        (*object)[std::string(property_name)] = property_value;

        token = this->stream->get_next_token();

        switch (token->getType()) {
            case Token::Type::Comma:
                // parse next object property key-val
                // todo: fixme, refactor
                goto PARSE_OBJ_PROPERTY;
            case Token::Type::BracesClose:
                break;
            default:
                // @todo: throw exception
                std::cout << "unexpected token while parse object: " << token->getType() << std::endl;
                return NULL;
        }

        // todo: allocate memory
        return object;
    }

    std::string* Decoder::parse_text() {
        Token::Token *token = this->stream->get_next_token();
        if (token->getType() != Token::Type::Text) {
            return NULL;
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
            // todo: throw exception
            return NULL;
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

        PARSE_ARRAY:
        element = this->parse_element();
        list->push_back(element);

        Token::Token *token = this->stream->get_next_token();
        if (token->getType() == Token::Type::Comma) {
            // repeat
            goto PARSE_ARRAY;
        }

        if (token->getType() != Token::Type::ArrayClose) {
            // throw exception
            return NULL;
        }

        return list;
    }
} // JsonStreamAnalyzer
