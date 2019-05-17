#include <map>
#include <string>

#define QUOTE_UNDEFINED -1
#define QUOTE_KEY_OPEN 0
#define QUOTE_KEY_CLOSE 1
#define QUOTE_VAL_OPEN 2
#define QUOTE_VAL_CLOSE 3
#define QUOTE_KEY_TEXT 4
#define QUOTE_COLON 5
#define QUOTE_VAL_TEXT 6

#define ELEMENT_TYPE_OBJECT 1
#define ELEMENT_TYPE_TEXT 2

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

    Object* _parse_object()
    {
        Object* obj = new Object();
        Token* token, keyToken, valToken;

        // json-объект
        token = this->stream->get_next_token();
        if (token->getType() != TOKEN_TYPE_BRACES_OPEN) {
            return NULL;
        }

        // флаги состояния
        int quoteMode = QUOTE_UNDEFINED;
        // конец

        token = this->stream->get_next_token();
        while (token != NULL) {
            switch (token->getType()) {
                case TOKEN_TYPE_QUOTES:
                    if (quoteMode == QUOTE_UNDEFINED) {
                        // открытие кавычек (название свойства json-объекта)
                        quoteMode = QUOTE_KEY_OPEN;
                    } else if (quoteMode == QUOTE_KEY_TEXT) {
                        // закрытие кавычек (название свойства json-объекта)
                        quoteMode = QUOTE_KEY_CLOSE;
                    } else if (quoteMode == QUOTE_COLON) {
                        quoteMode = QUOTE_VAL_OPEN;
                    } else if (quoteMode == QUOTE_VAL_TEXT) {
                        quoteMode = QUOTE_VAL_CLOSE;
                        // todo: save in object (keyToken => valToken)
                    }
                    break;
                case TOKEN_TYPE_TEXT:
                    if (quoteMode == QUOTE_KEY_OPEN) {
                        keyToken = token;
                        quoteMode = QUOTE_KEY_TEXT;
                    } else if (quoteMode == QUOTE_VAL_OPEN) {
                        quoteMode = QUOTE_VAL_TEXT;
                        valToken = token;
                    }
                    break;
                case TOKEN_TYPE_COLON:
                    if (quoteMode == QUOTE_KEY_CLOSE) {
                        quoteMode = QUOTE_COLON;
                    }
                    break;
            }

            token = this->stream->get_next_token();
        }

        return obj;
    }

    void parse_key_value_object(Object* obj)
    {
        Token* token = this->stream->get_next_token();
        if (token == NULL) {
            // invalid json
            return;
        }
        if (token->getType() != TOKEN_TYPE_QUOTES) {
            // invalid json
            return;
        }

        token = this->stream->get_next_token();
        if (token == NULL) {
            // invalid json
            return;
        }
        if (token->getType() != TOKEN_TYPE_TEXT) {
            // invalid json
            return;
        }

        // todo make key

        token = this->stream->get_next_token();
        if (token == NULL) {
            // invalid json
            return;
        }
        if (token->getType() != TOKEN_TYPE_QUOTES) {
            // invalid json
            return;
        }

        token = this->stream->get_next_token();
        if (token == NULL) {
            // invalid json
            return;
        }
        if (token->getType() != TOKEN_TYPE_COLON) {
            // invalid json
            return;
        }

        token = this->stream->get_next_token();
        switch (token->getType()) {
            case TOKEN_TYPE_BRACES_OPEN:
                // object
                break;
            case TOKEN_TYPE_QUOTES:
                // text
                break;
            case TOKEN_TYPE_ARRAY_OPEN:
                // array
                break;
            case TOKEN_TYPE_TEXT:
                // boolean
                break;
            case TOKEN_TYPE_NUMERIC:
                // digits
                break;
        }
    }
};
