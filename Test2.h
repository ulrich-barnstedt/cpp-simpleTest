//https://github.com/ulrich-barnstedt/cpp-simpleTest

#pragma once
#include <iostream>
#include <functional>
#include <vector>

#define T_TEST(name, content) G.RUN(#name, [] (TEST2::TEST_CONTEXT &T) content)
#define T_TEST_BINDING(name, vars, content) G.RUN(#name, [vars] (TEST2::TEST_CONTEXT &T) content)
#define T_GROUP(name, content) void testGroup__##name () { TEST2::GROUP_CONTEXT G (#name); content; G.RESULT(); }
#define T_EXPECT(condition) T.EXPECT(condition, #condition)
#define T_EXECUTE(group) testGroup__##group ()

namespace TEST2 {
    enum STATE {PASSED, FAILED};
    class TEST_RESULT {
        public:
            STATE result;
            std::string content;
            TEST_RESULT(STATE result, const std::string &content) {
                this->result = result;
                this->content = content;
            }
    };
    class TEST_CONTEXT {
        public:
            std::string testName;
            std::vector<TEST_RESULT> results;

            explicit TEST_CONTEXT(const std::string &testName) {
                this->testName = testName;
            }
            void EXPECT (bool value, const std::string &content) {
                this->results.emplace_back(value ? PASSED : FAILED, content);
            }
            [[nodiscard]] STATE allPassed () const {
                for (const TEST_RESULT &value : results) {
                    if (value.result == FAILED) return FAILED;
                }
                return PASSED;
            }
            void draw (bool last) const {
                STATE total = this->allPassed();
                std::cout << "  " << (last ? "└" : "├") <<"─── [" << (total == PASSED ? "PASSED" : "FAILED") << "] " << this->testName << std::endl;
                if (total == PASSED) return;

                for (const TEST_RESULT &res : results) {
                    std::cout << "  " << (last ? " " : "│") << "      ── [" << (res.result == PASSED ? "PASSED" : "FAILED") << "] " << res.content << std::endl;
                }
            }
    };
    class GROUP_CONTEXT {
        private:
            std::string groupName;
            std::vector<TEST_CONTEXT> results;
        public:
            explicit GROUP_CONTEXT(const std::string &groupName) {
                this->groupName = groupName;
            }
            void RUN(const std::string &testName, const std::function<void(TEST_CONTEXT &)> &testFN) {
                TEST_CONTEXT ctx(testName);
                testFN(ctx);

                results.push_back(ctx);
            }
            void RESULT() {
                std::cout << "──┬─ [GROUP] " << groupName << std::endl;
                for (unsigned int i = 0; i < results.size(); i++) {
                    results[i].draw(i == results.size() - 1);
                }
                std::cout << std::endl;
            }
    };
}