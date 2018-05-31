#include "AhoCorasick.h"

AhoCorasick::AhoCorasick() {
  bohr = NULL;
}

AhoCorasick::~AhoCorasick() {
  reset();
}
void AhoCorasick::init(const std::string& text, const std::string& joker_string, const char& joker) {
    this->text = text;
    this->joker_string = joker_string;
    this->joker = joker;
    bohr = new Bohr(text.size());
}
std::vector<int> AhoCorasick::solve() {
    std::vector<int> res = bohr->searchJoker(text, joker_string, joker);
    return res;
}
void AhoCorasick::reset() {
    if (bohr) delete bohr;
    joker_string.clear();
    text.clear();
}
