class Object
{
public:
    Object()
    {
        this->map = NULL;
        this->length = 0;
    }

    void setKeyValue(char* key, Value* value)
    {
    }

private:
    int length;
    DWORD* map;
};
