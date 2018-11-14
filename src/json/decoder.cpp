class Decoder
{
public:
    Decoder(Stream *stream)
    {
        this->stream = stream;
    }

private:
    Stream* stream;
};
