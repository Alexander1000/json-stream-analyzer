#include <json-stream-analyzer/element.h>

namespace JsonStreamAnalyzer {
    Element::Element(int type, void *data) {
        this->type = type;
        this->data = data;
    }
} // JsonStreamAnalyzer
