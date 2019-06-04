#include <iostream>
#include <string>

#include <tests.h>

#include <json-stream-analyzer.h>
#include <io-buffer.h>

class AssertElementTypeException
{};

class AssertObjectPropertyExist
{};

class AssertEqualsException
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

void assertEquals(Test::TestCase* testCase, std::string str1, std::string str2)
{
    testCase->increment();
    if (str1.compare(str2) != 0) {
        throw new AssertEqualsException;
    }
}

void assertEquals(Test::TestCase* testCase, std::string* str1, std::string str2)
{
    testCase->increment();
    if (str1->compare(str2) != 0) {
        throw new AssertEqualsException;
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

    JsonArray::iterator it = serviceList->begin();

    JsonStreamAnalyzer::Element* el1 = *it;
    assertType(t, el1, ELEMENT_TYPE_OBJECT);
    JsonObject* obj1 = (JsonObject*) el1->getData();
    assertObjectPropertyExist(t, obj1, "name");
    assertObjectPropertyExist(t, obj1, "description");
    // field: name
    JsonStreamAnalyzer::Element* obj1Name = obj1->at("name");
    assertType(t, obj1Name, ELEMENT_TYPE_TEXT);
    assertEquals(t, (std::string*) obj1Name->getData(), "Some-Name");
    // field: description
    JsonStreamAnalyzer::Element* obj1Descr = obj1->at("description");
    assertType(t, obj1Descr, ELEMENT_TYPE_TEXT);
    assertEquals(t, (std::string*) obj1Descr->getData(), "simple field");

    ++it;

    JsonStreamAnalyzer::Element* el2 = *it;
    assertType(t, el2, ELEMENT_TYPE_OBJECT);
    JsonObject* obj2 = (JsonObject*) el2->getData();
    assertObjectPropertyExist(t, obj2, "name");
    assertObjectPropertyExist(t, obj2, "value");
    // field: name
    JsonStreamAnalyzer::Element* obj2Name = obj2->at("name");
    assertType(t, obj2Name, ELEMENT_TYPE_TEXT);
    assertEquals(t, (std::string*) obj2Name->getData(), "Service-2");
    // field: value
    JsonStreamAnalyzer::Element* obj2Value = obj2->at("value");
    assertType(t, obj2Value, ELEMENT_TYPE_NUMERIC);
    assertEquals(t, (std::string*) obj2Value->getData(), "724");

    return t;
}

int main(int argc, char** argv) {
    Test::TestSuite testSuite;
    testSuite.addTestCase(testCase_SimpleExample_Positive());
    return 0;
}
