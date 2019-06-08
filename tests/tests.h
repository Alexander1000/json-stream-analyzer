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
            std::cout << ".";
        }

        char* getName()
        {
            return this->name;
        }

        int getAsserts()
        {
            return this->asserts;
        }

        void printTitle() {
            std::cout << "TestCase: " << this->name << std::endl;
        }

        void finish() {
            std::cout << std::endl;
            std::cout << "Total asserts: " << this->asserts << std::endl;
            std::cout << std::endl;
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
            this->testCaseList.push_back(testCase);
        }

    private:
        std::list<TestCase*> testCaseList;
    };
}

#endif
