// Copyright DimaZzZz101 2021

#ifndef BASICSTORAGE_HPP
#define BASICSTORAGE_HPP

#include <iostream>
#include <string>
#include <vector>

#include <cmath>

#include <sstream>
#include <fstream>
#include <filesystem>

// Абстрактный класс - базовый для классов: склад одежды и склад обуви
class BasicStorage {
public:
    BasicStorage();

    BasicStorage(std::string &Name, std::string &City, size_t Capacity);
    BasicStorage(BasicStorage *Data);

    std::string GetName();
    void SetName(std::string &Name);

    std::string GetCity();
    void SetCity(std::string &City);

    size_t GetCapacity();
    void SetCapacity(size_t Capacity);

    size_t GetFullness();
    void SetFullness(size_t Fullness);

    size_t GetPercentage();

    virtual std::string ToString() = 0;
    virtual void Print(std::ostream &Out = std::cout) = 0;
    virtual void Add(std::vector<std::string> Things) = 0;
    virtual void Remove(std::vector<std::string> Things) = 0;

    virtual ~BasicStorage() {
        Name_ = "";
        City_ = "";
        Capacity_ = 0u;
        Fullness_ = 0u;
    }
private:
    std::string Name_;
    std::string City_;
    size_t Capacity_ = 0u;
    size_t Fullness_ = 0u;
};

// Функция обработки строки входной строки
static std::vector<std::string> PrepareString(std::string Input, std::string Separator = " ") {
    Input += Separator;
    std::vector<std::string> PreparedString;

    size_t Pos;

    while ((Pos = Input.find(Separator)) != std::string::npos) {
        PreparedString.push_back(Input.substr(0, Pos));
        Input.erase(0, Pos + Separator.size());
    }

    PreparedString.erase(remove(PreparedString.begin(), PreparedString.end(), ""), PreparedString.end());

    return PreparedString;
}


#endif
