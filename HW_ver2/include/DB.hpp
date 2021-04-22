// Copyright DimaZzZz101 2021

#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>

#include <sstream>
#include <istream>
#include <filesystem>
#include <fstream>


#include "ShoesStorage.hpp"
#include "ClothesStorage.hpp"
#include "BasicStorage.hpp"


namespace fs = std::filesystem;

class DB {
public:
    DB(std::string &DBName, size_t DataBaseType);

    DB(std::string &DBName, size_t DataBaseType, std::vector<BasicStorage*> &Data);

    DB(std::string PATH);

    std::string GetName();
    void SetName(std::string &Name);

    size_t GetDBType();
    void SetDBType(size_t Type);

    BasicStorage *FindNode(std::string NodeName);


    std::string ToString();

    void Print();

    void Add(BasicStorage *Node);

    void Remove(std::string &Name);

    // Сортировка
    void Sort(std::string Param, bool Type);

    // Группировка
    std::vector<BasicStorage *> GroupByPercentage(const size_t Percentage);

    std::vector<BasicStorage *> GroupByCity(const std::string &CityName);

    void SaveFile(std::string Name = "\0");

    ~DB();

private:
    std::string DBName_;
    size_t DataBaseType_; // Тип БД // 0 - Гибрид, 1 - Вещи, 2 - Обувь
    std::vector<BasicStorage *> GeneralData_;

    // Функции-конпараторы
    static bool SortByName(BasicStorage *a, BasicStorage *b);
    static bool SortByNameDescending(BasicStorage *a, BasicStorage *b);

    static bool SortByCapacity(BasicStorage *a, BasicStorage *b);
    static bool SortByCapacityDescending(BasicStorage *a, BasicStorage *b);
};


#endif
