#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class Unit{
public:
Unit(const char& sym, const int& parent = -1)
    : sym(sym)
    , parent(parent)
    , end(false)
    , suffix_link(-1)
    , goodsuffix_link(-1)
{
    moves[sym] = -1;
    nextUnits[sym] = -1;
}
    std::map<char, int> nextUnits;
    std::map<char, int> moves;
    int pattern_number;
    int suffix_link;
    int goodsuffix_link;
    int parent;
    bool end;
    char sym;
};

typedef std::pair<int, int> result;

class Bohr {
public:
Bohr() {
    bohr.push_back(Unit('#'));
}

void addString(const std::string& pattern, const int& pattern_number) {

    int UnitNum = 0;

    for (unsigned int i = 0; i < pattern.size(); i++) {
        char sym = pattern[i];

        if ((bohr[UnitNum].nextUnits.find(sym) == bohr[UnitNum].nextUnits.end())
            || (bohr[UnitNum].nextUnits[sym] == -1)) {

              bohr.push_back(Unit(sym, UnitNum));
              bohr[UnitNum].nextUnits[sym] = bohr.size() - 1;
        }

        UnitNum = bohr[UnitNum].nextUnits[sym];
    }

    bohr[UnitNum].pattern_number = pattern_number;
    bohr[UnitNum].end = true;

}

int getAutoMoves(const int& UnitNum, const char& sym) {

    if (bohr[UnitNum].moves.find(sym) == bohr[UnitNum].moves.end()
        || bohr[UnitNum].moves[sym] == -1) {
  	     if (bohr[UnitNum].nextUnits.find(sym) != bohr[UnitNum].nextUnits.end()
              && bohr[UnitNum].nextUnits[sym] != -1) {
                  bohr[UnitNum].moves[sym] = bohr[UnitNum].nextUnits[sym];
        } else {
  			     if (UnitNum == 0) {
                bohr[UnitNum].moves[sym] = 0;
             } else {
                bohr[UnitNum].moves[sym] = getAutoMoves(getSuffixLink(UnitNum), sym);
             }
  		}
  	}

  return bohr[UnitNum].moves[sym];
}

int getSuffixLink(const int& UnitNum) {

    if (bohr[UnitNum].suffix_link == -1) {
        if (!(UnitNum && bohr[UnitNum].parent)) {
            bohr[UnitNum].suffix_link = 0;
        }
        else {
          bohr[UnitNum].suffix_link = getAutoMoves(getSuffixLink(
              bohr[UnitNum].parent), bohr[UnitNum].sym);
        }
    }

    return bohr[UnitNum].suffix_link;
}

int getSuffixGoodLink(const int& UnitNum) {

    if (bohr[UnitNum].goodsuffix_link == -1) {
        int teck = getSuffixLink(UnitNum);

        if (!teck) {
            bohr[UnitNum].goodsuffix_link = 0;
        } else {
            if (bohr[teck].end) {
                bohr[UnitNum].goodsuffix_link = teck;
            } else {
                bohr[UnitNum].goodsuffix_link = getSuffixGoodLink(teck);
            }
        }
    }

    return bohr[UnitNum].goodsuffix_link;
}

void check(const int& UnitNum, const int& i
          ,  const std::vector<std::string>& patterns
          ,  std::vector<result> &results) {

    for (int next = UnitNum; next; next = getSuffixGoodLink(next)) {
        if (bohr[next].end) {
            result temp(i - patterns[bohr[next].pattern_number].size() + 1,
                            bohr[next].pattern_number + 1);
            results.push_back(temp);
        }
    }
}

std::vector<result> search(const std::string& text, const std::vector<std::string>& patterns) {

    std::vector<result> res;

    int UnitNum = 0;
    for(unsigned i = 0; i < text.size(); i++) {
        UnitNum = getAutoMoves(UnitNum, text[i]);
        check(UnitNum, i + 1, patterns, res);
    }

    return res;
}
private:
    std::vector<Unit> bohr;
};



class AhoCorasick{
public:
AhoCorasick() {
  bohr = NULL;
}

~AhoCorasick() {
  reset();
}

void init(const std::string& text, const std::vector<std::string>& patterns, const unsigned int& numOfPatterns) {
    this->text = text;
    this->patterns = patterns;

    bohr = new Bohr;

    for (int i = 0; i < numOfPatterns; i++) {
        bohr->addString(patterns[i], i);
    }
}

static bool sortComparator(const result& a, const result& b) {
    return (a.first == b.first) ? (a.second < b.second) : (a.first < b.first);
}

std::vector<result> solve() {
    std::vector<result> res;
    if (!bohr) return res;
    res = bohr->search(text, patterns);
    std::sort(res.begin(), res.end(), sortComparator);

    return res;
}

void reset() {
    if (bohr) delete bohr;
    patterns.clear();
    text.clear();
}

private:

      std::string text;
      std::vector<std::string> patterns;
      Bohr* bohr;
};

int main() {
    std::string text;
    unsigned int numOfPatterns;

    std::cin >> text;
    std::cin >> numOfPatterns;
    std::vector<std::string> patterns(numOfPatterns);

    for (unsigned int i = 0; i < numOfPatterns; i++) {
        std::cin >> patterns[i];
    }

    AhoCorasick ahoCor;

    ahoCor.init(text, patterns, numOfPatterns);
    std::vector<result> results = ahoCor.solve();

    for (auto result : results) {
        std::cout << result.first << " " << result.second << std::endl;
    }

    return 0;
}
