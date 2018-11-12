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
        int offset = 0;

        bool needOffset = false;

        do {
            token = this->stream->get_next_token();
            if (token == NULL) {
                break;
            }

            if (needOffset) {
                this->print_offset(offset);
                needOffset = false;
            }

            switch (token->getType()) {
                case TOKEN_TYPE_BRACES_OPEN:
                    cout << "{" << endl;
                    offset++;
                    needOffset = true;
                    break;
                case TOKEN_TYPE_BRACES_CLOSE:
                    offset--;
                    cout << "}" << endl;
                    break;
                case TOKEN_TYPE_QUOTES:
                    cout << '"';
                    needOffset = false;
                    break;
                case TOKEN_TYPE_ARRAY_OPEN:
                    cout << "[" << endl;
                    needOffset = true;
                    offset++;
                    break;
                case TOKEN_TYPE_ARRAY_CLOSE:
                    offset--;
                    cout << endl;
                    this->print_offset(offset);
                    cout << "]" << endl;
                    needOffset = true;
                    break;
                case TOKEN_TYPE_COLON:
                    cout << ":";
                    break;
                case TOKEN_TYPE_COMMA:
                    cout << "," << endl;
                    needOffset = true;
                    break;
                case TOKEN_TYPE_TEXT:
                    reader = token->getReader();
                    char* text = new char[512];
                    reader->read(text, 512);
                    cout << text;
                    break;
            }
        } while (true);

        return;
    }
private:
    Stream *stream;

    void print_offset(int offset)
    {
        if (offset == 0) {
            return;
        }

        char *space = new char[offset * 4];
        memset(space, 0x20, offset * 4 * sizeof(char));
        cout << space;
    }
};
