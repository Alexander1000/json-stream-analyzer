class Pretty
{
public:
    Pretty(Stream *stream)
    {
        this->stream = stream;
    }

    void pretty()
    {
        Token *token;

        do {
            token = this->stream->get_next_token();
        } while (token != NULL);

        return;
    }
private:
    Stream *stream;
};
