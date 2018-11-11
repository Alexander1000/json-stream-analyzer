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
        IOReader* reader;

        do {
            token = this->stream->get_next_token();
            if (token != NULL) {
                reader = token->getReader();
                char* content = new char[512];
                reader->read(content, 512);
                cout << content << endl;
            }
        } while (token != NULL);

        return;
    }
private:
    Stream *stream;
};
