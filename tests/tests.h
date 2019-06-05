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
            this->name = (char*) name;
        }

        void increment()
        {
            this->asserts++;
        }
    private:
        char* name;
        int asserts = 0;
    };

    class TestSuite
    {
    public:
        TestSuite() {
        }

        void addTestCase(TestCase* testCase) {
            this->testCaseList.push_front(testCase);
        }

    private:
        std::list<TestCase*> testCaseList;
    };
}

#endif
