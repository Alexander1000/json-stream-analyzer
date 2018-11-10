class Stream
{
public:
    Stream(IOReader* reader)
    {
        this->reader = reader;

        this->currentBuffer = new char[STREAM_BUFFER_SIZE];
        this->forwardBuffer = new char[STREAM_BUFFER_SIZE];

        memset(this->currentBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
        memset(this->forwardBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
    }

private:
    IOReader* reader;

    char* currentBuffer;
    char* forwardBuffer;
};
