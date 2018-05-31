#ifndef BOHR_H
#define BOHR_H

#include "Unit.h"
#include <vector>

typedef std::pair<int, int> result;

class Bohr {
public:
Bohr(const int& size);
void addString(const std::string& pattern, const int& pattern_number);
int getAutoMoves(const int& UnitNum, const char& sym);
int getSuffixLink(const int& UnitNum);
int getSuffixGoodLink(const int& UnitNum);
void check(const int& UnitNum, const int& position,  std::vector<result> &results);
void checkJoker(const int& UnitNum,  const int& position, const int& joker_lenth);
std::vector<int> parseJoker(const std::string& joker_string, const char& joker);
std::vector<result> find(const std::string& string);
std::vector<int> searchJoker(const std::string& text, const std::string& joker_string,
                    const char& joker);
private:
    std::vector<Unit> bohr;
    std::vector<int> results;
    std::vector<int> parent;
    std::vector<int> len;
    std::vector<std::string> pattern_string;
};

#endif
