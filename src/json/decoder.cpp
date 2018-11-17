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
        Token *token;

        // json-объект
        token = this->stream->get_next_token();
        if (token->getType() != TOKEN_TYPE_BRACES_OPEN) {
            return NULL;
        }

        token = this->stream->get_next_token();
        while(token != NULL) {
            token = this->stream->get_next_token();
        }

        return obj;
    }
};
