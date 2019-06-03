#include <iostream>

#include <tests.h>

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

Test::TestCase* testCase_SimpleExample_Positive() {
    Test::TestCase* testCase = new Test::TestCase("001-simple-example");

    IOBuffer::IOFileReader file_buffer("../fixtures/001-simple-example.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();

    assertType(object, ELEMENT_TYPE_OBJECT);
    JsonObject* obj = (JsonObject*) object->getData();
    assertObjectPropertyExist(obj, "services");
    assertObjectPropertyExist(obj, "test-identical");

    return testCase;
}

int main(int argc, char** argv) {
    Test::TestSuite testSuite();
    testSuite.addTestCase(testCase_SimpleExample_Positive());
    return 0;
}
