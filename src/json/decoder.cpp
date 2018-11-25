#define QUOTE_UNDEFINED -1
#define QUOTE_KEY_OPEN 0
#define QUOTE_KEY_CLOSE 1
#define QUOTE_VAL_OPEN 2
#define QUOTE_VAL_CLOSE 3
#define QUOTE_KEY_TEXT 4
#define QUOTE_COLON 5
#define QUOTE_VAL_TEXT 6

class Decoder
{
public:
    Decoder(Stream *stream)
    {
        this->stream = stream;
    }

    Object* decode()
    {
        return this->parse_object();
    }

private:
    Stream* stream;

    Object* parse_object()
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

    void parse_key_value_object()
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
