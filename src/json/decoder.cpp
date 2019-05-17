#include <map>
#include <string>

#define ELEMENT_TYPE_OBJECT 1
#define ELEMENT_TYPE_TEXT 2
#define ELEMENT_TYPE_NUMERIC 3

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

        switch (token->getType()) {
            case TOKEN_TYPE_BRACES_OPEN:
                // object
                std::map<std::string, Element*>* obj = this->parse_object();
                element = new Element(ELEMENT_TYPE_OBJECT, (void*) obj);
                return element;
            case TOKEN_TYPE_QUOTES:
                // text
                std::string* text = this->parse_text();
                element = new Element(ELEMENT_TYPE_TEXT, (void*) text);
                return element;
            case TOKEN_TYPE_NUMERIC:
                // numeric
                std::string* digit = this->parse_numeric();
                element = new Element(ELEMENT_TYPE_NUMERIC, (void*) digit);
                return element;
        }

        return NULL;
    }

    std::map<std::string, Element*>* parse_object()
    {
        std::map<std::string, Element*> object;

        Token* token = this->stream->get_next_token();
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

        Element* property_value = this->parse_element();

        object[std::string(property_name)] = property_value;

        // todo: allocate memory
        return &object;
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
};
