#ifndef UNIT_H
#define UNIT_H

#include <map>
#include <vector>

class Unit{
public:
Unit(const char& sym, const int& parent = -1);
    std::map<char, int> nextUnits;
    std::map<char, int> moves;
    std::vector<int> pattern_number;

    int suffix_link;
    int goodsuffix_link;
    int parent;
    bool end;
    char sym;
};

#endif
