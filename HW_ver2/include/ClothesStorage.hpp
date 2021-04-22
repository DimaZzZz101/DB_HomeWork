// Copyright DimaZzZz101 2021

#ifndef CLOTHESSTORAGE_HPP
#define CLOTHESSTORAGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "BasicStorage.hpp"

class ClothesStorage : public BasicStorage {
public:
    ClothesStorage(std::string &Name, std::string &City, size_t Capacity);
    ClothesStorage(ClothesStorage *Data);
    ClothesStorage(std::string DBData);

    std::string ToString() override;
    void Print(std::ostream &Out = std::cout) override;
    void Add(std::vector<std::string> Clothes) override;
    void Remove(std::vector<std::string> Clothes) override;

private:
    // Структура для хранения данных - map,
    // т.к. удобно распределить характеристики одежды в складе.
    // Характеристики: Рост, размер, тип одежды, количество единиц товара
    std::map<std::pair<size_t, size_t>, std::map<std::string, size_t>> Clothes_;
};


#endif
