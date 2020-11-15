#include <json-stream-analyzer.h>
#include <io-buffer.h>
#include <string>
#include <memory.h>

namespace JsonStreamAnalyzer
{
    Encoder::Encoder() {

    }

    std::string* Encoder::encode(Element *element)
    {
        IOBuffer::IOMemoryBuffer memBuf;

        switch (element->getType()) {
            case ELEMENT_TYPE_OBJECT: {
                memBuf.write((char*) "{", 1);
                auto obj = (JsonObject *) element->getData();
                memBuf.write((char*) "}", 1);
                break;
            }
            case ELEMENT_TYPE_TEXT:
                auto strValue = (std::string*) element->getData();
                memBuf.write((char*) "\"", 1);
                memBuf.write((char*) strValue->c_str(), strValue->length());
                memBuf.write((char*) "\"", 1);
                break;
        }

        char* result = new char[1024];
        memset(result, 0, sizeof(char) * 1024);

        memBuf.setPosition(0);
        memBuf.read(result, 1024);

        std::string* strResult;
        strResult = new std::string(result);
        return strResult;
    }
}
