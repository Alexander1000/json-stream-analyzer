#include <map>
#include <string>
#include <list>
#include <iostream>

#include <json-stream-analyzer/element.h>
#include <json-stream-analyzer/stream.h>
#include <json-stream-analyzer/token.h>

namespace JsonStreamAnalyzer {

    class Decoder {
    public:
        Decoder(Stream *stream) {
            this->stream = stream;
        }

        Element *decode() {
            return this->parse();
        }

    private:
        Stream *stream;

        Element *parse() {
            return this->parse_element();
        }

        Element *parse_element() {
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
                case TOKEN_TYPE_BRACES_OPEN:
                    // object
                    obj = this->parse_object();
                    element = new Element(ELEMENT_TYPE_OBJECT, (void *) obj);
                    return element;
                case TOKEN_TYPE_QUOTES:
                    // text
                    text = this->parse_text();
                    element = new Element(ELEMENT_TYPE_TEXT, (void *) text);
                    return element;
                case TOKEN_TYPE_NUMERIC:
                    // numeric
                    digit = this->parse_numeric();
                    element = new Element(ELEMENT_TYPE_NUMERIC, (void *) digit);
                    return element;
                case TOKEN_TYPE_ARRAY_OPEN:
                    // array
                    array = this->parse_array();
                    element = new Element(ELEMENT_TYPE_ARRAY, (void *) array);
                    return element;
            }

            return NULL;
        }

        std::map<std::string, Element *> *parse_object() {
            std::map<std::string, Element *> *object;
            object = new std::map<std::string, Element *>;

            Token::Token *token;

            PARSE_OBJ_PROPERTY:
            token = this->stream->get_next_token();
            if (token->getType() != TOKEN_TYPE_QUOTES) {
                // unexpected, object property must be have quote
                // @todo: throw exception
                return NULL;
            }

            token = this->stream->get_next_token();
            if (token->getType() != TOKEN_TYPE_TEXT) {
                // unexpected
                // @todo: throw exception
                return NULL;
            }

            // @todo: optimize and reuse (memory managment)
            char *property_name = (char *) malloc(sizeof(char *) * 1024);
            token->getReader()->read(property_name, 1024);

            token = this->stream->get_next_token();
            if (token->getType() != TOKEN_TYPE_QUOTES) {
                // @todo: throw exception
                return NULL;
            }

            token = this->stream->get_next_token();
            if (token->getType() != TOKEN_TYPE_COLON) {
                // @todo: unexpected
                return NULL;
            }

            Element *property_value = this->parse_element();

            (*object)[std::string(property_name)] = property_value;

            token = this->stream->get_next_token();
            switch (token->getType()) {
                case TOKEN_TYPE_COMMA:
                    // parse next object property key-val
                    // todo: fixme, refactor
                    goto PARSE_OBJ_PROPERTY;
                case TOKEN_TYPE_BRACES_CLOSE:
                    break;
            }

            // todo: allocate memory
            return object;
        }

        std::string *parse_text() {
            Token::Token *token = this->stream->get_next_token();
            if (token->getType() != TOKEN_TYPE_TEXT) {
                return NULL;
            }

            std::string *val;
            if (token->getReader() == NULL) {
                // empty token
                val = new std::string("");
            } else {
                char *text = (char *) malloc(sizeof(char *) * 1024);
                token->getReader()->read(text, 1024);
                val = new std::string(text);
            }

            token = this->stream->get_next_token();
            if (token->getType() != TOKEN_TYPE_QUOTES) {
                // todo: throw exception
                return NULL;
            }

            return val;
        }

        std::string *parse_numeric() {
            Token::Token *token = this->stream->get_next_token();
            if (token->getType() != TOKEN_TYPE_NUMERIC) {
                return NULL;
            }

            char *text = (char *) malloc(sizeof(char *) * 1024);
            token->getReader()->read(text, 1024);
            std::string *val = new std::string(text);
            return val;
        }

        std::list<Element *> *parse_array() {
            std::list<Element *> *list;
            list = new std::list<Element *>;
            Element *element;

            PARSE_ARRAY:
            element = this->parse_element();
            list->push_back(element);

            Token::Token *token = this->stream->get_next_token();
            if (token->getType() == TOKEN_TYPE_COMMA) {
                // repeat
                goto PARSE_ARRAY;
            }

            if (token->getType() != TOKEN_TYPE_ARRAY_CLOSE) {
                // throw exception
                return NULL;
            }

            return list;
        }
    };

} // JsonStreamAnalyzer
