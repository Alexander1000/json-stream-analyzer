class Object
{
public:
    Object(Stream *stream)
    {
        this->stream = stream;
    }

private:
    Stream* stream;
};
