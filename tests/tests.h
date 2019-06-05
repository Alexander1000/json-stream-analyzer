#ifndef TESTS_H
#define TESTS_H

#include <list>
#include <iostream>

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

        char* getName()
        {
            return this->name;
        }

        int getAsserts()
        {
            return this->asserts;
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

        void print() {
            for (std::list<TestCase*>::iterator iTestCase = this->testCaseList.begin(); iTestCase != this->testCaseList.end(); ++iTestCase) {
                std::cout << "<------>" << std::endl;
                std::cout << "TestCase: " << (*iTestCase)->getName() << std::endl;
                std::cout << "Asserts: " << (*iTestCase)->getAsserts() << std::endl;
            }
        }

    private:
        std::list<TestCase*> testCaseList;
    };
}

#endif
