#include <iostream>
#include "AhoCorasick.h"


int main() {
    std::string text;
    std::string joker_string;
    char joker;

    std::cin >> text;
    std::cin >> joker_string;
    std::cin >> joker;

    AhoCorasick ahoCorAlgorithm;

    ahoCorAlgorithm.init(text, joker_string, joker);
    std::vector<int> res = ahoCorAlgorithm.solve();
    for (int result : res) {
        std::cout << result << std::endl;
    }

    return 0;
}
