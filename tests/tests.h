#ifndef TESTS_H
#define TESTS_H

#include <list>

namespace Test
{
    class TestCase
    {
    public:
        TestCase(const char* name)
        {
            this->name = name;
        }
    private:
        char* name;
    };

    class TestSuite
    {
    public:
        TestSuite() {
            this->testCaseList = std::list<TestCase>();
        }

        void addTestCase(TestCase testCase) {
            this->testCaseList.push_front(testCase);
        }
    private:
        std::list<TestCase> testCaseList;
    };
}

#endif
