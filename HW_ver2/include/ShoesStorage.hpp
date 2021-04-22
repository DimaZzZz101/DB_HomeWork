// Copyright DimaZzZz101 2021

#ifndef SHOESSTORAGE_HPP
#define SHOESSTORAGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "BasicStorage.hpp"


class ShoesStorage : public BasicStorage {
public:

    ShoesStorage(std::string &Name, std::string &City, size_t Capacity);
    ShoesStorage(ShoesStorage *Data);
    ShoesStorage(std::string DBData);

    std::string ToString() override;
    void Print(std::ostream &Out = std::cout) override;
    void Add(std::vector<std::string> Shoes) override;
    void Remove(std::vector<std::string> Shoes) override;

private:
    // Структура для хранения данных - map,
    // т.к. удобно распределить характеристики одежды в складе.
    // Характеристики: Размер, тип одежды, количество единиц товара
    std::map<size_t, std::map<std::string, size_t>> Shoes_;

};


#endif
