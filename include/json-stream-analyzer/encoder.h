#ifndef JSON_ANALYZER_ENCODER_H
#define JSON_ANALYZER_ENCODER_H

#include <string>
#include <json-stream-analyzer/element.h>

namespace JsonStreamAnalyzer
{
    class Encoder
    {
    public:
        Encoder();
        std::string* encode(Element* element);
    };
}

#endif
