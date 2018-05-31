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
{}
    std::map<char, int> nextUnits;
    std::map<char, int> moves;
    std::vector<int> pattern_number;

    int suffix_link;
    int goodsuffix_link;
    int parent;
    bool end;
    char sym;
};

typedef std::pair<int, int> result;

class Bohr {
public:
Bohr(const int& size) {
    bohr.push_back(Unit(-1));
    parent = std::vector<int>(size,0);
}

void addString(const std::string& pattern, const int& pattern_number) {

    int UnitNum = 0;

    for (unsigned int i = 0; i < pattern.size(); i++) {
        char sym = pattern[i];

        if (bohr[UnitNum].nextUnits.find(sym) == bohr[UnitNum].nextUnits.end()) {
              bohr.push_back(Unit(sym, UnitNum));
              bohr[UnitNum].nextUnits[sym] = bohr.size() - 1;
        }

        UnitNum = bohr[UnitNum].nextUnits[sym];
    }

    bohr[UnitNum].pattern_number.push_back(pattern_number);
    bohr[UnitNum].end = true;

}

int getAutoMoves(const int& UnitNum, const char& sym) {

    if (bohr[UnitNum].moves.find(sym) == bohr[UnitNum].moves.end()){
  	     if (bohr[UnitNum].nextUnits.find(sym) != bohr[UnitNum].nextUnits.end()) {
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

void check(const int& UnitNum, const int& position,  std::vector<result> &results) {
    for (int next = UnitNum; next != 0; next = getSuffixGoodLink(next)) {
        if (bohr[next].end) {
            results.push_back({position - pattern_string[bohr[next].pattern_number.back()].size() + 1,
                            bohr[next].pattern_number.back() + 1});
        }
    }
}

void checkJoker(const int& UnitNum,  const int& position, const int& joker_lenth) {
    for (int next = UnitNum; next != 0; next = getSuffixGoodLink(next)) {
        if (bohr[next].end)
            for (int j = 0; j < bohr[next].pattern_number.size(); ++j) {
                int difference = position - len[bohr[next].pattern_number[j]];
                if((difference >= 0)&&((++parent[difference]) == len.size()) &&
                    (parent.size() - difference >= joker_lenth))
                            results.push_back(difference +1);
            }
    }
}
std::vector<int> parseJoker(const std::string& joker_string, const char& joker) {
    std::vector <int> length;
    std::string temp;
    for(int i = 0; i < joker_string.length(); ++i) {
        if((joker_string[i] == joker) && (temp.length() > 0)) {
            length.push_back(i);
            addString(temp,length.size() - 1);
            temp.clear();
        }
        else if (joker_string[i] != joker){
            temp.push_back(joker_string[i]);
            if ((i == (joker_string.length() - 1)) && temp.length()) {
                length.push_back(i + 1);
                addString(temp, length.size() - 1);
            }
        }
    }
    return length;
}

std::vector<result> find(const std::string& string) {
    for (size_t i = 0; i < pattern_string.size(); i++) {
        addString(pattern_string[i], i);
    }
  	std::vector <result> res;
  	int unit = 0;

  	for (int i = 0; i < string.length(); i++) {
  		  unit = getAutoMoves(unit, string[i]);
  		  check(unit, i + 1, res);
  	}
  	return res;
}
std::vector<int> searchJoker(const std::string& text, const std::string& joker_string,
                    const char& joker) {
    len = parseJoker(joker_string,joker);
    int unit = 0;
    for(int i = 0;i < text.length(); ++i) {
        unit = getAutoMoves(unit, text[i]);
        checkJoker(unit, i + 1, joker_string.size());
    }
    return results;
}
private:
    std::vector<Unit> bohr;
    std::vector<int> results;
    std::vector<int> parent;
    std::vector<int> len;
    std::vector<std::string> pattern_string;
};



class AhoCorasick{
public:
AhoCorasick() {
  bohr = NULL;
}

~AhoCorasick() {
  reset();
}

void init(const std::string& text, const std::string& joker_string, const char& joker) {
    this->text = text;
    this->joker_string = joker_string;
    this->joker = joker;
    bohr = new Bohr(text.size());
}

std::vector<int> solve() {
    std::vector<int> res = bohr->searchJoker(text, joker_string, joker);
    return res;
}

void reset() {
    if (bohr) delete bohr;
    joker_string.clear();
    text.clear();
}

private:
      std::string text;
      std::string joker_string;
      char joker;
      Bohr* bohr;
};

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
