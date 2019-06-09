#include <iostream>
#include <string>

#include <json-stream-analyzer.h>
#include <io-buffer.h>
#include <cpp-unit-test.h>

class AssertElementTypeException
{};

class AssertObjectPropertyExist
{};

typedef std::map<std::string, JsonStreamAnalyzer::Element*> JsonObject;
typedef std::list<JsonStreamAnalyzer::Element*> JsonArray;

void assertType(CppUnitTest::TestCase* testCase, JsonStreamAnalyzer::Element* element, int expectedType) {
    testCase->increment();

    if (element->getType() != expectedType) {
        std::cout << "Expected element type: " << expectedType << "; but given: " << element->getType() << std::endl;
        throw new AssertElementTypeException;
    }
}

void assertType(CppUnitTest::TestCase* testCase, JsonStreamAnalyzer::Element* element, int expectedType, const char* field) {
    testCase->increment();

    if (element->getType() != expectedType) {
        std::cout << "Expected element '" << field << "' type: " << expectedType << "; but given: " << element->getType() << std::endl;
        throw new AssertElementTypeException;
    }
}

void assertObjectPropertyExist(CppUnitTest::TestCase* testCase, JsonObject* obj, const char* propertyName) {
    testCase->increment();

    if (obj->find(propertyName) == obj->end()) {
        throw new AssertObjectPropertyExist;
    }
}

CppUnitTest::TestCase* testCase_SimpleExample_Positive() {
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("001-simple-example");
    t->printTitle();

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

    t->finish();
    return t;
}

CppUnitTest::TestCase* testCase_BoolData_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("002-bool-data");
    t->printTitle();

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

    t->finish();
    return t;
}

CppUnitTest::TestCase* testCase_DataWithNull_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("003-data-with-null");
    t->printTitle();

    IOBuffer::IOFileReader file_buffer("../fixtures/003-data-with-null.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();

    assertType(t, object, ELEMENT_TYPE_OBJECT);
    JsonObject* obj = (JsonObject*) object->getData();
    assertObjectPropertyExist(t, obj, "digit");
    assertObjectPropertyExist(t, obj, "str");
    assertObjectPropertyExist(t, obj, "isNullable");
    assertObjectPropertyExist(t, obj, "simple");

    JsonStreamAnalyzer::Element* elDigit = obj->at("digit");
    assertType(t, elDigit, ELEMENT_TYPE_NUMERIC);
    assertEquals(t, "42", (std::string*) elDigit->getData());

    JsonStreamAnalyzer::Element* elStr = obj->at("str");
    assertType(t, elStr, ELEMENT_TYPE_TEXT);
    assertEquals(t, "it is text", (std::string*) elStr->getData());

    JsonStreamAnalyzer::Element* elIsNullable = obj->at("isNullable");
    assertType(t, elIsNullable, ELEMENT_TYPE_NULL);

    JsonStreamAnalyzer::Element* elSimple = obj->at("simple");
    assertType(t, elSimple, ELEMENT_TYPE_BOOL);
    assertFalse(t, (bool) elSimple->getData());

    t->finish();
    return t;
}

CppUnitTest::TestCase* testCase_FixturedData004_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("004-fixtured-data");
    t->printTitle();

    IOBuffer::IOFileReader file_buffer("../fixtures/004-sample-for-test.json");
    JsonStreamAnalyzer::Stream json_stream(&file_buffer);
    JsonStreamAnalyzer::Decoder decoder(&json_stream);
    JsonStreamAnalyzer::Element* object = decoder.decode();

    assertType(t, object, ELEMENT_TYPE_OBJECT);
    JsonObject* obj = (JsonObject*) object->getData();
    assertEquals(t, 4, obj->size());
    assertObjectPropertyExist(t, obj, "someObject");
    assertObjectPropertyExist(t, obj, "test");
    assertObjectPropertyExist(t, obj, "fifif");
    assertObjectPropertyExist(t, obj, "another");

    // JsonPointer: /someObject
    JsonStreamAnalyzer::Element* elSomeObject = obj->at("someObject");
    assertType(t, elSomeObject, ELEMENT_TYPE_NUMERIC);
    assertEquals(t, "12", (std::string*) elSomeObject->getData());

    // JsonPointer: /test
    JsonStreamAnalyzer::Element* elTest = obj->at("test");
    assertType(t, elTest, ELEMENT_TYPE_NUMERIC, "/test");
    assertEquals(t, "43.24", (std::string*) elTest->getData());

    // JsonPointer: /fifif
    JsonStreamAnalyzer::Element* elFifif = obj->at("fifif");
    assertType(t, elFifif, ELEMENT_TYPE_TEXT, "/fifif");
    assertEquals(t, "fdasfd", (std::string*) elFifif->getData());

    // JsonPointer: /another
    JsonStreamAnalyzer::Element* elAnother = obj->at("another");
    assertType(t, elAnother, ELEMENT_TYPE_ARRAY, "/another");
    JsonArray* aAnother = (JsonArray*) elAnother->getData();

    JsonArray::iterator iAnother = aAnother->begin();

    // JsonPointer: /another/0

    JsonStreamAnalyzer::Element* elAnother1 = *iAnother;
    assertType(t, elAnother1, ELEMENT_TYPE_OBJECT);
    JsonObject* obj1 = (JsonObject*) elAnother1->getData();
    assertEquals(t, 4, obj1->size());
    assertObjectPropertyExist(t, obj1, "tst");
    assertObjectPropertyExist(t, obj1, "value");
    assertObjectPropertyExist(t, obj1, "test");
    assertObjectPropertyExist(t, obj1, "aarr");

    // JsonPointer: /another/0/tst

    JsonStreamAnalyzer::Element* elTst = obj1->at("tst");
    assertType(t, elTst, ELEMENT_TYPE_TEXT, "/another/0/tst");
    assertEquals(t, "fsdf", (std::string*) elTst->getData());

    // JsonPointer: /another/0/value

    JsonStreamAnalyzer::Element* elValue = obj1->at("value");
    assertType(t, elValue, ELEMENT_TYPE_NUMERIC, "/another/0/value");
    assertEquals(t, "342.34", (std::string*) elValue->getData());

    // JsonPointer: /another/0/test

    JsonStreamAnalyzer::Element* elAnother0Test = obj1->at("test");
    assertType(t, elAnother0Test, ELEMENT_TYPE_BOOL);
    assertFalse(t, (bool) elAnother0Test->getData());

    // JsonPointer: /another/0/aarr

    JsonStreamAnalyzer::Element* elNestedObj = obj1->at("aarr");
    assertType(t, elNestedObj, ELEMENT_TYPE_OBJECT, "/another/0/aarr");
    JsonObject* oNestedObj = (JsonObject*) elNestedObj->getData();
    assertEquals(t, 7, oNestedObj->size());
    assertObjectPropertyExist(t, oNestedObj, "figator");
    assertObjectPropertyExist(t, oNestedObj, "invalid");
    assertObjectPropertyExist(t, oNestedObj, "ass");
    assertObjectPropertyExist(t, oNestedObj, "adf");
    assertObjectPropertyExist(t, oNestedObj, "gadss");
    assertObjectPropertyExist(t, oNestedObj, "someTest");
    assertObjectPropertyExist(t, oNestedObj, "parent");

    // JsonPointer: /another/0/aarr/figator

    JsonStreamAnalyzer::Element* elFigator = oNestedObj->at("figator");
    assertType(t, elFigator, ELEMENT_TYPE_TEXT, "/another/0/aarr/figator");
    assertEquals(t, "fas", (std::string*) elFigator->getData());

    // JsonPointer: /another/0/aarr/invalid

    JsonStreamAnalyzer::Element* elInvalid = oNestedObj->at("invalid");
    assertType(t, elInvalid, ELEMENT_TYPE_BOOL, "/another/0/aarr/invalid");
    assertTrue(t, (bool) elInvalid->getData());

    // JsonPointer: /another/0/aarr/ass

    JsonStreamAnalyzer::Element* elAss = oNestedObj->at("ass");
    assertType(t, elAss, ELEMENT_TYPE_NUMERIC, "/another/0/aarr/ass");
    assertEquals(t, "45", (std::string*) elAss->getData());

    // JsonPointer: /another/0/aarr/adf

    JsonStreamAnalyzer::Element* elAdf = oNestedObj->at("adf");
    assertType(t, elAdf, ELEMENT_TYPE_ARRAY);
    JsonArray* aAdf = (JsonArray*) elAdf->getData();
    assertEquals(t, 3, aAdf->size());

    JsonArray::iterator iAdf = aAdf->begin();

    // JsonPointer: /another/0/aarr/adf/0

    JsonStreamAnalyzer::Element* elAdf01 = *iAdf;
    assertType(t, elAdf01, ELEMENT_TYPE_NUMERIC, "/another/0/aarr/adf/0");
    assertEquals(t, "34", (std::string*) elAdf01->getData());

    iAdf++;

    // JsonPointer: /another/0/aarr/adf/1

    JsonStreamAnalyzer::Element* elAdf02 = *iAdf;
    assertType(t, elAdf02, ELEMENT_TYPE_NUMERIC, "/another/0/aarr/adf/1");
    assertEquals(t, "324", (std::string*) elAdf02->getData());

    iAdf++;

    // JsonPointer: /another/0/aarr/adf/2

    JsonStreamAnalyzer::Element* elAdf03 = *iAdf;
    assertType(t, elAdf03, ELEMENT_TYPE_NUMERIC, "/another/0/aarr/adf/2");
    assertEquals(t, "43543.63", (std::string*) elAdf03->getData());

    // JsonPointer: /another/0/aarr/gadss

    JsonStreamAnalyzer::Element* elGadss = oNestedObj->at("gadss");
    assertType(t, elGadss, ELEMENT_TYPE_ARRAY, "/another/0/aarr/gadss");
    JsonArray* aGadds = (JsonArray*) elGadss->getData();

    JsonArray::iterator iGadds = aGadds->begin();

    // JsonPointer: /another/0/aarr/gadss/0

    JsonStreamAnalyzer::Element* elGadds01 = *iGadds;
    assertType(t, elGadds01, ELEMENT_TYPE_TEXT, "/another/0/aarr/gadss/0");
    assertEquals(t, "tet", (std::string*) elGadds01->getData());

    iGadds++;

    // JsonPointer: /another/0/aarr/gadss/1

    JsonStreamAnalyzer::Element* elGadds02 = *iGadds;
    assertType(t, elGadds02, ELEMENT_TYPE_TEXT, "/another/0/aarr/gadss/1");
    assertEquals(t, "test", (std::string*) elGadds02->getData());

    iGadds++;

    // JsonPointer: /another/0/aarr/gadss/2

    JsonStreamAnalyzer::Element* elGadds03 = *iGadds;
    assertType(t, elGadds03, ELEMENT_TYPE_TEXT, "/another/0/aarr/gadss/2");
    assertEquals(t, "sdfs", (std::string*) elGadds03->getData());

    // JsonPointer: /another/0/aarr/someTest

    JsonStreamAnalyzer::Element* elSomeTest = oNestedObj->at("someTest");
    assertType(t, elSomeTest, ELEMENT_TYPE_TEXT, "/another/0/aarr/someTest");
    assertEquals(t, "fdsdfs\"fdfs", (std::string*) elSomeTest->getData());

    // JsonPointer: /another/0/aarr/parent

    JsonStreamAnalyzer::Element* elParent = oNestedObj->at("parent");
    assertType(t, elParent, ELEMENT_TYPE_NULL, "/another/0/aarr/parent");

    ++iAnother;

    // JsonPointer: /another/1
    JsonStreamAnalyzer::Element* elAnother2 = *iAnother;
    assertType(t, elAnother2, ELEMENT_TYPE_OBJECT);
    JsonObject* obj2 = (JsonObject*) elAnother2->getData();
    assertObjectPropertyExist(t, obj2, "tags");
    assertObjectPropertyExist(t, obj2, "fixes");

    // JsonPointer: /another/1/tags

    JsonStreamAnalyzer::Element* elTags = obj2->at("tags");
    assertType(t, elTags, ELEMENT_TYPE_OBJECT, "/another/1/tags");
    JsonObject* oTags = (JsonObject*) elTags->getData();
    assertEquals(t, 0, oTags->size());

    // JsonPointer: /another/1/fixes

    JsonStreamAnalyzer::Element* elFixes = obj2->at("fixes");
    JsonArray* aFixes = (JsonArray*) elFixes->getData();
    assertEquals(t, 0, aFixes->size());

    t->finish();
    return t;
}

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;

    std::cout << std::endl;

    testSuite.addTestCase(testCase_SimpleExample_Positive());

    std::cout << std::endl;

    testSuite.addTestCase(testCase_BoolData_Positive());

    std::cout << std::endl;

    testSuite.addTestCase(testCase_DataWithNull_Positive());

    std::cout << std::endl;

    testSuite.addTestCase(testCase_FixturedData004_Positive());

    std::cout << std::endl;

    testSuite.printTotal();

    return 0;
}
