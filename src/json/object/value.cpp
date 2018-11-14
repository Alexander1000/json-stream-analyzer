class Value
{
public:
    Value(int type, void* data)
    {
        this->type = type;
        this->data = data;
    }

    int getType()
    {
        return this->type;
    }

    void* getData()
    {
        return this->data;
    }
private:
    int type;
    void* data;
};
