#pragma once
#include <iostream>
#include <functional>

namespace TEST {
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

    void UNIT(const std::function<void(T &ctx)> &FN) {
        T ctx;
        FN(ctx);

        ctx.results();
    }
}
