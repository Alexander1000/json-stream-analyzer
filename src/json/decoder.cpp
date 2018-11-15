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
        return obj;
    }

private:
    Stream* stream;
};
