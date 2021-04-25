// Copyright DimaZzZz101 2021

#include "../include/ClothesStorage.hpp"

ClothesStorage::ClothesStorage(std::string &Name, std::string &City, size_t Capacity) :
        BasicStorage(Name, City, Capacity) {}

ClothesStorage::ClothesStorage(ClothesStorage *Data) : BasicStorage(Data) { Clothes_ = Data->Clothes_; }

ClothesStorage::ClothesStorage(std::string DBData) {

    // Первый этап отбора основной информации о складе
    std::vector<std::string> BasicStorageData = PrepareString(DBData, "#\n");

    // Второй этап отбора основной информации о складе
    std::vector<std::string> BasicStorageInfo = PrepareString(BasicStorageData[0], "\n");

    // Заполнение полей основной информации о складе
    SetName(BasicStorageInfo[0]); // Название склада
    SetCity(BasicStorageInfo[1]); // Название города
    SetCapacity(std::stoi(BasicStorageInfo[2])); // Вместимость склада
    SetFullness(std::stoi(BasicStorageInfo[3])); // Заполненность склада


    // Третий этап отбора информации: информация об одежде
    for (size_t i = 1; i < BasicStorageData.size(); ++i) {
        // Вся информация об одежде
        std::vector<std::string> ClothesData = PrepareString(BasicStorageData[i], "\n");

        // Берем данные конкретной позиции одежды на складе
        std::vector<std::string> ClothesInfo = PrepareString(ClothesData[0]);

        // Берем информацию о росте и размере, связываем их
        std::pair<size_t, size_t> ClothesSize(std::stoi(ClothesInfo[0]), std::stoi(ClothesInfo[1]));

        for (size_t j = 1; j < ClothesData.size(); ++j) {
            // Берем оставшуюся информацию о типе одежды и ее количестве на складе
            std::vector<std::string> OtherClothesData = PrepareString(ClothesData[j]);

            // Заполнение map-a
            Clothes_[ClothesSize][OtherClothesData[0]] = std::stoi(OtherClothesData[1]);
        }
    }
}

// Функия записи в файл
std::string ClothesStorage::ToString() {
    std::stringstream out;
    // Пишем в файл идикатор типа склада С - Clothes
    out << "C\n";
    out << GetName() << std::endl << GetCity() << std::endl << GetCapacity() << std::endl << GetFullness() << std::endl;

    for (auto it1 : Clothes_) {
        out << "#" << std::endl << it1.first.first << " " << it1.first.second << std::endl;
        for (auto it2 : it1.second)
        {
            out << it2.first << " " << it2.second << std::endl;
        }
    }

    return out.str();
}

// Функция вывода в консоль
void ClothesStorage::Print(std::ostream &Out) {
    // Вывод основной информации
    Out << "Clothes Storage" << std::endl << "Name: " << GetName() << std::endl
        << "City: " << GetCity() << std::endl << "Capacity: " << GetCapacity() << std::endl
        << "Fullness: " << GetFullness() << std::endl << std::endl;

    if (!Clothes_.empty()) Out << "Items:\n\n";
    for (auto it1 : Clothes_) {
        // Вывод информации о размере
        Out << "Size: " << it1.first.first << ", " << it1.first.second << std::endl;

        // Вывод информации о типе и количестве данного типа
        for (auto it2 : it1.second) {
            Out << "\tType: " << it2.first << "\n\t\tCount: " << it2.second << std::endl;
        }

        Out << std::endl;
    }
}

// Функция довления вещей в склад
void ClothesStorage::Add(std::vector<std::string> Clothes) {
    // Если нет места на складе
    if (GetFullness() + std::stoi(Clothes[3]) > GetCapacity()) throw "No space for new clothes";

    std::string Type = Clothes[0];
    std::pair<size_t, size_t> Size(std::stoi(Clothes[1]), std::stoi(Clothes[2]));
    size_t Count = std::stoi(Clothes[3]);

    Clothes_[Size][Type] += Count;
    SetFullness(GetFullness() + Count);
}

// Удаление вещй со склада
void ClothesStorage::Remove(std::vector<std::string> Clothes) {
    std::string Type = Clothes[0]; // Получаем тип одежды

    // Связываем размер и рост для последующего взаимодействия
    std::pair<size_t, size_t> Size(std::stoi(Clothes[1]), std::stoi(Clothes[2]));

    size_t Count; // Переменная для хранения количества единиц товара на складе

    // Если встречено слово all то выбираем по двум параметрам, не учитывая количество пар обуви
    if (Clothes[3] == "all") {
        Count = Clothes_[Size][Type];
        // в противном случае берем количество по позиции [2] в map-e
    } else {
        Count = std::stoi(Clothes[3]);
    }

    // Если запись на складе пустая
    if (Clothes_.find(Size) == Clothes_.end()) throw "There are no such things";

    // Если нечего удалять
    if (Clothes_[Size][Type] < Count) { throw "Not enough count to remove"; }

    Clothes_[Size][Type] -= Count; // Вносим изменения в количестве единиц

    SetFullness(GetFullness() - Count); // Устанавливаем соответствующую заполненность

    // Удаляем пустую запись
    if (Clothes_[Size][Type] == 0) {
        Clothes_[Size].erase(Type);
        if (Clothes_[Size].empty()) { Clothes_.erase(Size); }
    }
}

