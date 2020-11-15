#ifndef JSON_ANALYZER_ENCODER_H
#define JSON_ANALYZER_ENCODER_H

#include <string>
#include <map>
#include <io-buffer.h>
#include <json-stream-analyzer/element.h>

typedef std::map<std::string, JsonStreamAnalyzer::Element*> JsonObject;

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
