//https://github.com/ulrich-barnstedt/cpp-simpleTest

#pragma once
#include <iostream>
#include <functional>

//macros to make definition of tests easier
#define T_UNIT(Group, Name, Executes) TEST::NamedUnit([] (TEST::T &T) Executes, Group, Name);
#define T_BINDING_UNIT(Group, Name, Binds, Executes) TEST::NamedUnit([Binds] (TEST::T &T) Executes, Group, Name); //define manually for binding multiple vars
#define T_EXPECT(Expression) T.EXPECT(Expression);
#define T_CONTEXT (TEST::T &T)

namespace TEST {
    //class T represents the "test-context" specific data
    class T {
    private:
        int assertionsFailed;
        int assertionsPassed;
        int totalAssertions;
        std::string group;
        std::string name;
    public:
        T() {
            totalAssertions = 0;
            assertionsPassed = 0;
            assertionsFailed = 0;

            group = "<no group>";
            name = "<no name>";
        }
        void CONTAINS (const std::string &group, const std::string &name) {
            this->group = group;
            this->name = name;
        }
        void EXPECT(bool value) {
            totalAssertions++;

            if (value) {
                assertionsPassed++;
            } else {
                assertionsFailed++;
            }
        }
        void results () {
            std::cout << "──┬─ TEST " << group << "." << name << std::endl;
            std::cout << "  │ " << assertionsFailed << " failed / " << totalAssertions << " assertions" << std::endl;
            std::cout << "  │ " << ">> " << (assertionsPassed == totalAssertions ? "PASSED" : "FAILED") << "\n" << std::endl;
        }
    };

    //Create a test unit
    //Name can be specified with T.CONTAINS in the test itself
    void Unit(const std::function<void(T &ctx)> &FN) {
        T ctx;
        FN(ctx);

        ctx.results();
    }

    //Create a test unit with name pre-defined
    void NamedUnit (const std::function<void(T &ctx)> &FN, const std::string &group, const std::string &name) {
        T ctx;
        ctx.CONTAINS(group, name);
        FN(ctx);

        ctx.results();
    }
}