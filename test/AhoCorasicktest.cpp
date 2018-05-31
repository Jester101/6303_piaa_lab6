#include <gtest/gtest.h>
#include "../AhoCorasick/src/AhoCorasick.h"
#include <iostream>

struct TestAhoCorasick : testing::Test {
    AhoCorasick* ahoCorAlgorithm;
    TestAhoCorasick();
    ~TestAhoCorasick();
};

TestAhoCorasick::TestAhoCorasick() {
    ahoCorAlgorithm = new AhoCorasick;
}

TestAhoCorasick::~TestAhoCorasick() {
    delete ahoCorAlgorithm;
}

struct testState {
    std::string text;
    unsigned int patterns_number;
    std::vector<std::string> patterns;
    std::vector<result> results;

    friend std::ostream& operator<<(std::ostream& os, const testState& obj) {
        os << "[" << std::endl;
        os << "Text: " << std::endl;
        os << "\t" << obj.text << std::endl;
        os << "patterns_number: " << std::endl;
        os << "\t" << obj.patterns_number << std::endl;
        os << "Patterns: " << std::endl;
        for (auto pattern : obj.patterns) {
            os << "\t" << pattern << std::endl;
        }
        os << "Results: " << std::endl;

        for (auto res : obj.results) {
            os << "\t" << res.first << " " << res.second << std::endl;
        }

        os << "]" <<std::endl;

        return os;
    }
};

struct patternsSearchTest : TestAhoCorasick, testing::WithParamInterface<testState> {
    void SetUp() {
        std::cout << GetParam();
    }
};

TEST_P(patternsSearchTest, searchPatternsInText) {
    auto state = GetParam();
    ahoCorAlgorithm->init(state.text, state.patterns, state.patterns_number);
    ASSERT_EQ(state.results, ahoCorAlgorithm->solve());
}


INSTANTIATE_TEST_CASE_P(Default, patternsSearchTest,
  testing::Values(
  testState{"CCCA", 1, {"CC"}, {{1, 1}, {2, 1}}},
  testState{"CCCA", 1, {"CAC"}, {}},
  testState{"dfghjkjhgffrgthyjuikjhgfrfgth", 5, {"ff", "ab", "i", "rgthy", "gh"}, {{3, 5}, {10, 1}, {12, 4  }, {19, 3}}},
  testState{"KEKTESTKEKTSTRTRTRTLLLALLAEJ", 3, {"KEK", "STR", "L"}, {{1, 1}, {8, 1}, {12, 2}, {20, 3}, {21, 3}, {22, 3}, {24, 3},
  {25, 3}}}
  // Update: cyrillic symbols
));

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
