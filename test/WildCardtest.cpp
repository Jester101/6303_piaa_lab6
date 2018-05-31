#include <gtest/gtest.h>
#include "../WildCard/src/AhoCorasick.h"
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
    std::string joker_string;
    char joker;
    std::vector<int> results;

    friend std::ostream& operator<<(std::ostream& os, const testState& obj) {

        os << "[" << std::endl;
        os << "Text: " << std::endl;
        os << "\t" << obj.text << std::endl;
        os << "JokerString: " << std::endl;
        os << "\t" << obj.joker_string << std::endl;
        os << "Joker: " << std::endl;
        os << "\t" << obj.joker << std::endl;

        os << "Results: " << std::endl;

        for (auto result : obj.results) {
            os << "\t" << result << std::endl;
        }

        os << "]" <<std::endl;

        return os;
    }
};

struct jokerSearchTest : TestAhoCorasick, testing::WithParamInterface<testState> {
    void SetUp() {
        std::cout << GetParam();
    }
};

TEST_P(jokerSearchTest, searchWithWildcard) {
    auto state = GetParam();
    ahoCorAlgorithm->init(state.text, state.joker_string, state.joker);
    ASSERT_EQ(state.results, ahoCorAlgorithm->solve());
}


INSTANTIATE_TEST_CASE_P(Default, jokerSearchTest,
  testing::Values(
  testState{"AACT", "A$", '$', {1, 2}},
  testState{"AACT", "T$", '$', {}},
  testState{"AACT", "$A$", '$', {1}},
  testState{"AAAAAAAANAN", "$$$", '$', {}},
  testState{"WILDSEARCHTEST","$S$A", '$', {4}},
  testState{"ABBAABBAAABA", "$a$", '$', {}},
  testState{"ABBAABBAAABA", "$A$", '$', {3, 4, 7, 8, 9}}
  // Update: cyrillic symbols
  ));

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
