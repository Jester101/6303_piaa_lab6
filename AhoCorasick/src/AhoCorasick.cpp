#include "AhoCorasick.h"

#include <algorithm>

AhoCorasick::AhoCorasick() {
  bohr = NULL;
}

AhoCorasick::~AhoCorasick() {
  reset();
}

void AhoCorasick::init(const std::string& text, const std::vector<std::string>& patterns, const unsigned int& numOfPatterns) {
    this->text = text;
    this->patterns = patterns;

    bohr = new Bohr;

    for (int i = 0; i < numOfPatterns; i++) {
        bohr->addString(patterns[i], i);
    }
}

std::vector<result> AhoCorasick::solve() {
    std::vector<result> res;
    if (!bohr) return res;
    res = bohr->search(text, patterns);
    std::sort(res.begin(), res.end(), sortComparator);

    return res;
}

void AhoCorasick::reset() {
    if (bohr) delete bohr;
    patterns.clear();
    text.clear();
}

bool AhoCorasick::sortComparator(const result& a, const result& b) {
    return (a.first == b.first) ? (a.second < b.second) : (a.first < b.first);
}
