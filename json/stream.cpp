class Stream
{
public:
    Stream(IOReader* reader)
    {
        this->reader = reader;
    }

private:
    IOReader* reader;
};
