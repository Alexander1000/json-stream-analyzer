#include <iostream>

#include <tests.h>

#include <json-stream-analyzer.h>
#include <io-buffer.h>

class AssertElementTypeException
{};

class AssertObjectPropertyExist
{};

typedef std::map<std::string, JsonStreamAnalyzer::Element*> JsonObject;
typedef std::list<JsonStreamAnalyzer::Element*> JsonArray;

void assertType(Test::TestCase* testCase, JsonStreamAnalyzer::Element* element, int expectedType) {
    testCase->increment();

    if (element->getType() != expectedType) {
        std::cout << "Expected element type: " << expectedType << "; but given: " << element->getType() << std::endl;
        throw new AssertElementTypeException;
    }
}

void assertObjectPropertyExist(Test::TestCase* testCase, JsonObject* obj, const char* propertyName) {
    testCase->increment();

    if (obj->find(propertyName) == obj->end()) {
        throw new AssertObjectPropertyExist;
    }
}

Test::TestCase* testCase_SimpleExample_Positive() {
    Test::TestCase* t = new Test::TestCase("001-simple-example");

    IOBuffer::IOFileReader file_buffer("../fixtures/001-simple-example.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();

    assertType(t, object, ELEMENT_TYPE_OBJECT);
    JsonObject* obj = (JsonObject*) object->getData();
    assertObjectPropertyExist(t, obj, "services");
    assertObjectPropertyExist(t, obj, "test-identical");

    JsonStreamAnalyzer::Element* servicesObject = obj->at("services");
    assertType(t, servicesObject, ELEMENT_TYPE_ARRAY);
    JsonArray* serviceList = (JsonArray*) servicesObject->getData();

    return t;
}

int main(int argc, char** argv) {
    Test::TestSuite testSuite;
    testSuite.addTestCase(testCase_SimpleExample_Positive());
    return 0;
}
