#include <iostream>

#include <json-stream-analyzer.h>
#include <io-buffer.h>

class AssertElementTypeException
{};

class AssertObjectPropertyExist
{};

typedef std::map<std::string, JsonStreamAnalyzer::Element *> JsonObject;

void assertType(JsonStreamAnalyzer::Element* element, int expectedType) {
    if (element->getType() != expectedType) {
        std::cout << "Expected element type: " << expectedType << "; but given: " << element->getType() << std::endl;
        throw new AssertElementTypeException;
    }
}

void assertObjectPropertyExist(JsonObject* obj, const char* propertyName) {
    if (obj->find(propertyName) == obj->end()) {
        throw new AssertObjectPropertyExist;
    }
}

int main(int argc, char** argv) {
    IOBuffer::IOFileReader file_buffer("../fixtures/001-simple-example.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();

    assertType(object, ELEMENT_TYPE_OBJECT);
    JsonObject* obj = (JsonObject*) object->getData();
    assertObjectPropertyExist(obj, "services");
    assertObjectPropertyExist(obj, "test-identical");

    return 0;
}
