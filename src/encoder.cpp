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
                for (auto itObj = obj->begin(); itObj != obj->end(); itObj++) {
                    memBuf.write((char*) "\"", 1);
                    memBuf.write((char*) itObj->first.c_str(), itObj->first.length());
                    memBuf.write((char*) "\"", 1);
                    memBuf.write((char*) ":", 1);

                    auto nestedResult = this->encode(itObj->second);
                    memBuf.write((char*) nestedResult->c_str(), nestedResult->length());

                    auto itNextObj = itObj;
                    itNextObj++;
                    if (itNextObj != obj->end()) {
                        memBuf.write((char*) ",", 1);
                    }
                }
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
