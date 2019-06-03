#include <iostream>

#include <json-stream-analyzer.h>
#include <io-buffer.h>

class AssertElementTypeException
{};

void assertType(JsonStreamAnalyzer::Element* element, int expectedType) {
    if (element->getType() != expectedType) {
        std::cout << "Expected element type: " << expectedType << "; but given: " << element->getType() << std::endl;
        throw new AssertElementTypeException;
    }
}

int main(int argc, char** argv) {
    IOBuffer::IOFileReader file_buffer("../fixtures/001-simple-example.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();

    assertType(object, ELEMENT_TYPE_OBJECT);

    return 0;
}
