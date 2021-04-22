// Copyright DimaZzZz101 2021

#include "../include/ShoesStorage.hpp"


ShoesStorage::ShoesStorage(std::string &Name, std::string &City, size_t Capacity) :
        BasicStorage(Name, City, Capacity) {}

ShoesStorage::ShoesStorage(ShoesStorage *Data) : BasicStorage(Data) { Shoes_ = Data->Shoes_; }

ShoesStorage::ShoesStorage(std::string DBData) {

    // Первый этап отбора основной информации о складе
    std::vector<std::string> BasicStorageData = PrepareString(DBData, "#\n");

    // Второй этап отбора основной информации о складе
    std::vector<std::string> BasicStorageInfo = PrepareString(BasicStorageData[0], "\n");

    // Заполнение полей основной информации о складе
    SetName(BasicStorageInfo[0]); // Название склада
    SetCity(BasicStorageInfo[1]); // Название города
    SetCapacity(std::stoi(BasicStorageInfo[2])); // Вместимость склада
    SetFullness(std::stoi(BasicStorageInfo[3])); // Заполненность склада

    for (size_t i = 1; i < BasicStorageData.size(); ++i) {
        // Заполняем массив с данными об обуви
        std::vector<std::string> ShoesData = PrepareString(BasicStorageData[i], "\n");

        // Берем из него информацию о размере
        size_t Size = std::stoi(ShoesData[0]);

        // Записываем оставшуюся информацию об обуви сопоставляя ее с соответствующим размером
        for (size_t j = 1; j < ShoesData.size(); ++j) {
            std::vector<std::string> OtherShoesData = PrepareString(ShoesData[j]);
            Shoes_[Size][OtherShoesData[0]] = std::stoi(OtherShoesData[1]);
        }
    }
}

std::string ShoesStorage::ToString() {
    std::stringstream out;

    out << "S\n";
    out << GetName() << std::endl << GetCity() << std::endl << GetCapacity() << std::endl << GetFullness() << std::endl;

    for (auto it1 : Shoes_) {
        out << "#" << std::endl << it1.first << std::endl;
        for (auto it2 : it1.second)
        {
            out << it2.first << " " << it2.second << std::endl;
        }
    }

    return out.str();
}

void ShoesStorage::Print(std::ostream &Out) {
    // Вывод основной информации
    Out << "Clothes Storage" << std::endl << "Name: " << GetName() << std::endl
        << "City: " << GetCity() << std::endl << "Capacity: " << GetCapacity() << std::endl
        << "Fullness: " << GetFullness() << std::endl << std::endl;

    if (!Shoes_.empty()) Out << "Items:\n\n";
    for (auto it1 : Shoes_) {
        // Вывод информации о размере
        Out << "Size: " << it1.first << std::endl;

        // Вывод информации о типе и количестве данного типа
        for (auto it2 : it1.second) {
            Out << "\tType: " << it2.first << "\n\t\tCount: " << it2.second << std::endl;
        }

        Out << std::endl;
    }
}

void ShoesStorage::Add(std::vector<std::string> Shoes) {
    // Если нет места на складе
    if (GetFullness() + std::stoi(Shoes[2])) throw "No space for new clothes";

    std::string Type = Shoes[0]; // Информация о типе обуви
    size_t Size = std::stoi(Shoes[1]); // Информация о размере обуви
    size_t Count = std::stoi(Shoes[2]); // Информация о количестве пар данного типа

    Shoes_[Size][Type] += Count;
    SetFullness(GetFullness() + Count);
}

void ShoesStorage::Remove(std::vector<std::string> Shoes) {
    std::string Type = Shoes[0];
    size_t Size = std::stoi(Shoes[1]);
    size_t Count;

    /// узнать что делает
    if (Shoes[2] == "all") {
        Count = Shoes_[Size][Type];
    } else {
        Count = std::stoi(Shoes[2]);
    }

    if (Shoes_[Size][Type] - Count < 0) throw "Not enough count to remove";

    Shoes_[Size][Type] -= Count;

    SetFullness(GetFullness() - Count);

    if (Shoes_[Size][Type] == 0) {
        Shoes_[Size].erase(Type);
        if (Shoes_[Size].empty()) Shoes_.erase(Size);
    }
}
