#ifndef BOHR_H
#define BOHR_H

#include "Unit.h"
#include <vector>

typedef std::pair<int, int> result;

struct Bohr {

    Bohr();

    void addString(const std::string&, const int&);

    // Получение перехода автомат
    int getAutoMoves(const int&, const char&);

    // Получение суффиксальной ссылки
    int getSuffixLink(const int&);

    // Получение "хорошей" суффиксальной ссылки
    int getSuffixGoodLink(const int&);

    // Проверка
    void check(const int&, const int&, const std::vector<std::string>&, std::vector<result>&);

    // Поиск
    std::vector<result> search(const std::string&, const std::vector<std::string>&);


    // Данные
    std::vector<Unit> bohr;
};

#endif
