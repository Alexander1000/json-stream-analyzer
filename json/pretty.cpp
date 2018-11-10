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
            if (token != NULL) {
                cout << "Column: " << token->getColumn() << endl;
                cout << "Line: " << token->getLine() << endl;
            }
        } while (token != NULL);

        return;
    }
private:
    Stream *stream;
};
