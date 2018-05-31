#include "Bohr.h"


Bohr::Bohr() {
    bohr.push_back(Unit('$'));
}

void Bohr::addString(const std::string& pattern, const int& pattern_number) {

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

int Bohr::getAutoMoves(const int& UnitNum, const char& sym) {

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

int Bohr::getSuffixLink(const int& UnitNum) {

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

int Bohr::getSuffixGoodLink(const int& UnitNum) {

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

void Bohr::check(const int& UnitNum, const int& i
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

std::vector<result> Bohr::search(const std::string& text, const std::vector<std::string>& patterns) {

    std::vector<result> res;

    int UnitNum = 0;
    for(unsigned i = 0; i < text.size(); i++) {
        UnitNum = getAutoMoves(UnitNum, text[i]);
        check(UnitNum, i + 1, patterns, res);
    }

    return res;
}
