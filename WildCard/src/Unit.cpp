#include "Unit.h"

Unit::Unit(const char& sym, const int& parent)
    : sym(sym)
    , parent(parent)
    , end(false)
    , suffix_link(-1)
    , goodsuffix_link(-1)
{}
