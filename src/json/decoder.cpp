class Decoder
{
public:
    Decoder(Stream *stream)
    {
        this->stream = stream;
    }

    Object* decode()
    {
        Object* obj = new Object();
        Token *token;

        // begin // временное решение, json может начаться массивом
        token = this->stream->get_next_token();
        if (token->getType() != TOKEN_TYPE_BRACES_OPEN) {
            return NULL;
        }
        // end //

        token = this->stream->get_next_token();
        while(token != NULL) {
            token = this->stream->get_next_token();
        }

        return obj;
    }

private:
    Stream* stream;
};
