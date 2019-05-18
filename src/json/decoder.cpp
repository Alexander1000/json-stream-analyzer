#include <map>
#include <string>
#include <list>
#include <iostream>

#define ELEMENT_TYPE_OBJECT 1
#define ELEMENT_TYPE_TEXT 2
#define ELEMENT_TYPE_NUMERIC 3
#define ELEMENT_TYPE_ARRAY 4

class Decoder
{
public:
    Decoder(Stream *stream)
    {
        this->stream = stream;
    }

    Element* decode()
    {
        return this->parse();
    }

private:
    Stream* stream;

    Element* parse()
    {
        return this->parse_element();
    }

    Element* parse_element()
    {
        Token* token = this->stream->get_next_token();
        if (token == NULL) {
            return NULL;
        }

        Element* element;
        std::map<std::string, Element*>* obj;
        std::string* text;
        std::string* digit;
        std::list<Element*>* array;

        switch (token->getType()) {
            case TOKEN_TYPE_BRACES_OPEN:
                std::cout << "token object" << std::endl;
                // object
                obj = this->parse_object();
                element = new Element(ELEMENT_TYPE_OBJECT, (void*) obj);
                return element;
            case TOKEN_TYPE_QUOTES:
                std::cout << "token text" << std::endl;
                // text
                text = this->parse_text();
                element = new Element(ELEMENT_TYPE_TEXT, (void*) text);
                return element;
            case TOKEN_TYPE_NUMERIC:
                std::cout << "token numeric" << std::endl;
                // numeric
                digit = this->parse_numeric();
                element = new Element(ELEMENT_TYPE_NUMERIC, (void*) digit);
                return element;
            case TOKEN_TYPE_ARRAY_OPEN:
                std::cout << "token array" << std::endl;
                // array
                array = this->parse_array();
                element = new Element(ELEMENT_TYPE_ARRAY, (void*) array);
                return element;
        }

        return NULL;
    }

    std::map<std::string, Element*>* parse_object()
    {
        std::map<std::string, Element*>* object;
        object = new std::map<std::string, Element*>;

        Token* token;

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
        char* property_name = (char*) malloc(sizeof(char*) * 1024);
        token->getReader()->read(property_name, 1024);

        std::cout << "property_name: " << property_name << std::endl;

        token = this->stream->get_next_token();
        if (token->getType() != TOKEN_TYPE_QUOTES) {
            // @todo: throw exception
            // std::cout << "given: " << token->getType() << std::endl;
            return NULL;
        }

        token = this->stream->get_next_token();
        if (token->getType() != TOKEN_TYPE_COLON) {
            // std::cout << "given: " << token->getType() << std::endl;
            // @todo: unexpected
            return NULL;
        }

        Element* property_value = this->parse_element();

        (*object)[std::string(property_name)] = property_value;

        token = this->stream->get_next_token();
        switch (token->getType()) {
            case TOKEN_TYPE_COMMA:
                std::cout << "next property" << std::endl;
                // parse next object property key-val
                // todo: fixme, refactor
                goto PARSE_OBJ_PROPERTY;
            case TOKEN_TYPE_BRACES_CLOSE:
                break;
        }

        // todo: allocate memory
        return object;
    }

    std::string* parse_text()
    {
        Token* token = this->stream->get_next_token();
        if (token->getType() != TOKEN_TYPE_TEXT) {
            return NULL;
        }

        char* text = (char*) malloc(sizeof(char*) * 1024);
        token->getReader()->read(text, 1024);
        std::string* val = new std::string(text);

        token = this->stream->get_next_token();
        if (token->getType() != TOKEN_TYPE_QUOTES) {
            // todo: throw exception
            return NULL;
        }

        return val;
    }

    std::string* parse_numeric()
    {
        Token* token = this->stream->get_next_token();
        if (token->getType() != TOKEN_TYPE_NUMERIC) {
            return NULL;
        }

        char* text = (char*) malloc(sizeof(char*) * 1024);
        token->getReader()->read(text, 1024);
        std::string* val = new std::string(text);
        return val;
    }

    std::list<Element*>* parse_array()
    {
        std::list<Element*>* list;
        list = new std::list<Element*>;
        Element* element;

PARSE_ARRAY:
        element = this->parse_element();
        list->push_back(element);

        Token* token = this->stream->get_next_token();
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
