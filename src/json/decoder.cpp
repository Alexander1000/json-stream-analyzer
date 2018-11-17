#define QUOTE_UNDEFINED -1
#define QUOTE_KEY_OPEN 0
#define QUOTE_KEY_CLOSE 1
#define QUOTE_VAL_OPEN 2
#define QUOTE_VAL_CLOSE 3
#define QUOTE_KEY_TEXT 4

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
        Token* token, keyToken;

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
                    }
                    if (quoteMode == QUOTE_KEY_TEXT) {
                        // закрытие кавычек (название свойства json-объекта)
                        quoteMode = QUOTE_KEY_CLOSE;
                    }
                    break;
                case TOKEN_TYPE_TEXT:
                    if (quoteMode == QUOTE_KEY_OPEN) {
                        keyToken = token;
                        quoteMode = QUOTE_KEY_TEXT;
                    }
                    break;
            }

            token = this->stream->get_next_token();
        }

        return obj;
    }
};
