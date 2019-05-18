#define ELEMENT_TYPE_OBJECT 1
#define ELEMENT_TYPE_TEXT 2
#define ELEMENT_TYPE_NUMERIC 3
#define ELEMENT_TYPE_ARRAY 4

class Element
{
public:
    Element(int type, void* data);
};
