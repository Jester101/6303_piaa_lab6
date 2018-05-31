#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include "Bohr.h"
#include <algorithm>

class AhoCorasick{
public:
AhoCorasick();
~AhoCorasick();
void init(const std::string& text, const std::string& joker_string, const char& joker);
std::vector<int> solve();
void reset();
private:
      std::string text;
      std::string joker_string;
      char joker;
      Bohr* bohr;
};

#endif
