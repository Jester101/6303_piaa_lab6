#ifndef UNIT_H
#define UNIT_H

#include <map>

struct Unit {

    Unit(const char& sym, const int& parent = -1);
    std::map<char, int> nextUnits;
    std::map<char, int> moves;
    int pattern_number;
    int suffix_link;
    int goodsuffix_link;
    int parent;
    bool end;
    char sym;

};

#endif
