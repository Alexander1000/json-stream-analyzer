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

class AssertTrueException
{};

class AssertFalseException
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

void assertEquals(Test::TestCase* testCase, std::string str1, std::string* str2)
{
    testCase->increment();
    if (str1.compare(*str2) != 0) {
        throw new AssertEqualsException;
    }
}

void assertTrue(Test::TestCase* testCase, bool actual)
{
    testCase->increment();
    if (!actual) {
        throw new AssertTrueException;
    }
}

void assertFalse(Test::TestCase* testCase, bool actual)
{
    testCase->increment();
    if (actual) {
        throw new AssertFalseException;
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

    // JsonPointer: /services

    JsonStreamAnalyzer::Element* servicesObject = obj->at("services");
    assertType(t, servicesObject, ELEMENT_TYPE_ARRAY);
    JsonArray* serviceList = (JsonArray*) servicesObject->getData();

    JsonArray::iterator it = serviceList->begin();

    // JsonPointer: /services/0
    JsonStreamAnalyzer::Element* el1 = *it;
    assertType(t, el1, ELEMENT_TYPE_OBJECT);
    JsonObject* obj1 = (JsonObject*) el1->getData();
    assertObjectPropertyExist(t, obj1, "name");
    assertObjectPropertyExist(t, obj1, "description");
    // JsonPointer: /services/0/name
    JsonStreamAnalyzer::Element* obj1Name = obj1->at("name");
    assertType(t, obj1Name, ELEMENT_TYPE_TEXT);
    assertEquals(t, (std::string*) obj1Name->getData(), "Some-Name");
    // JsonPointer: /services/0/description
    JsonStreamAnalyzer::Element* obj1Descr = obj1->at("description");
    assertType(t, obj1Descr, ELEMENT_TYPE_TEXT);
    assertEquals(t, (std::string*) obj1Descr->getData(), "simple field");

    ++it;

    // JsonPointer: /services/1
    JsonStreamAnalyzer::Element* el2 = *it;
    assertType(t, el2, ELEMENT_TYPE_OBJECT);
    JsonObject* obj2 = (JsonObject*) el2->getData();
    assertObjectPropertyExist(t, obj2, "name");
    assertObjectPropertyExist(t, obj2, "value");
    // JsonPointer: /services/1/name
    JsonStreamAnalyzer::Element* obj2Name = obj2->at("name");
    assertType(t, obj2Name, ELEMENT_TYPE_TEXT);
    assertEquals(t, (std::string*) obj2Name->getData(), "Service-2");
    // JsonPointer: /services/1/value
    JsonStreamAnalyzer::Element* obj2Value = obj2->at("value");
    assertType(t, obj2Value, ELEMENT_TYPE_NUMERIC);
    assertEquals(t, (std::string*) obj2Value->getData(), "724");

    // JsonPointer: /test-identical

    JsonStreamAnalyzer::Element* elTestIdentical = obj->at("test-identical");
    assertType(t, elTestIdentical, ELEMENT_TYPE_OBJECT);
    JsonObject* oTestIdentical = (JsonObject*) elTestIdentical->getData();
    assertObjectPropertyExist(t, oTestIdentical, "someProperty");

    // JsonPointer: /test-identical/someProperty

    JsonStreamAnalyzer::Element* elSomeProperty = oTestIdentical->at("someProperty");
    assertType(t, elSomeProperty, ELEMENT_TYPE_OBJECT);
    JsonObject* oSomeProperty = (JsonObject*) elSomeProperty->getData();
    assertObjectPropertyExist(t, oSomeProperty, "currentProperty");
    assertObjectPropertyExist(t, oSomeProperty, "currentValue");

    // JsonPointer: /test-identical/someProperty/currentProperty

    JsonStreamAnalyzer::Element* elCurrentProperty = oSomeProperty->at("currentProperty");
    assertType(t, elCurrentProperty, ELEMENT_TYPE_OBJECT);
    JsonObject* oCurrentProperty = (JsonObject*) elCurrentProperty->getData();
    assertObjectPropertyExist(t, oCurrentProperty, "values");

    // JsonPointer: /test-identical/someProperty/currentProperty/values

    JsonStreamAnalyzer::Element* elValues = oCurrentProperty->at("values");
    assertType(t, elValues, ELEMENT_TYPE_ARRAY);
    JsonArray* aValues = (JsonArray*) elValues->getData();

    JsonArray::iterator iValues = aValues->begin();

    // JsonPointer: /test-identical/someProperty/currentProperty/values/0

    JsonStreamAnalyzer::Element* elValues0 = *iValues;
    assertType(t, elValues0, ELEMENT_TYPE_NUMERIC);
    assertEquals(t, "123", (std::string*) elValues0->getData());

    // JsonPointer: /test-identical/someProperty/currentProperty/values/1

    ++iValues;
    JsonStreamAnalyzer::Element* elValues1 = *iValues;
    assertType(t, elValues1, ELEMENT_TYPE_NUMERIC);
    assertEquals(t, "456", (std::string*) elValues1->getData());

    // JsonPointer: /test-identical/someProperty/currentProperty/values/2

    ++iValues;
    JsonStreamAnalyzer::Element* elValues2 = *iValues;
    assertType(t, elValues2, ELEMENT_TYPE_NUMERIC);
    assertEquals(t, "789", (std::string*) elValues2->getData());

    // JsonPointer: /test-identical/someProperty/currentValue

    JsonStreamAnalyzer::Element* elCurrentValue = oSomeProperty->at("currentValue");
    assertType(t, elCurrentValue, ELEMENT_TYPE_TEXT);
    assertEquals(t, "some-test", (std::string*) elCurrentValue->getData());

    return t;
}

Test::TestCase* testCase_BoolData_Positive()
{
    Test::TestCase* t = new Test::TestCase("002-bool-data");

    IOBuffer::IOFileReader file_buffer("../fixtures/002-bool-data.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();

    assertType(t, object, ELEMENT_TYPE_OBJECT);
    JsonObject* obj = (JsonObject*) object->getData();
    assertObjectPropertyExist(t, obj, "isPositive");
    assertObjectPropertyExist(t, obj, "isNegative");

    JsonStreamAnalyzer::Element* elIsPositive = obj->at("isPositive");
    assertType(t, elIsPositive, ELEMENT_TYPE_BOOL);
    assertTrue(t, (bool) elIsPositive->getData());

    JsonStreamAnalyzer::Element* elIsNegative = obj->at("isNegative");
    assertType(t, elIsNegative, ELEMENT_TYPE_BOOL);
    assertFalse(t, (bool) elIsNegative->getData());

    return t;
}

Test::TestCase* testCase_DataWithNull_Positive()
{
    Test::TestCase* t = new Test::TestCase("003-data-with-null");

    IOBuffer::IOFileReader file_buffer("../fixtures/003-data-with-null.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();

    return t;
}

int main(int argc, char** argv) {
    Test::TestSuite testSuite;

    std::cout << "===================================" << std::endl;
    std::cout << "= testCase_SimpleExample_Positive =" << std::endl;
    std::cout << "===================================" << std::endl;
    std::cout << std::endl;

    testSuite.addTestCase(testCase_SimpleExample_Positive());

    std::cout << std::endl;

    std::cout << "==============================" << std::endl;
    std::cout << "= testCase_BoolData_Positive =" << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl;

    testSuite.addTestCase(testCase_BoolData_Positive());

    std::cout << std::endl;

    std::cout << "==================================" << std::endl;
    std::cout << "= testCase_DataWithNull_Positive =" << std::endl;
    std::cout << "==================================" << std::endl;

    std::cout << std::endl;

    testSuite.addTestCase(testCase_DataWithNull_Positive());

    std::cout << std::endl;

    testSuite.print();
    return 0;
}
