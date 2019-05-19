#ifndef DECODER_INCLUDED
#define DECODER_INCLUDED

#include <json-stream-analyzer/element.h>

namespace JsonStreamAnalyzer {
    class Decoder {
    public:
        Decoder(Stream *stream);
        Element *decode();
    };
}

#endif /* DECODER_INCLUDED */