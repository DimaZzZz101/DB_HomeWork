// Copyright DimaZzZz101 2021

#include "../include/BasicStorage.hpp"

BasicStorage::BasicStorage() {}

BasicStorage::BasicStorage(std::string &Name, std::string &City, size_t Capacity) :
        Name_(Name), City_(City), Capacity_(Capacity) {}

BasicStorage::BasicStorage(BasicStorage *Data) {
    Name_ = Data->Name_;
    City_ = Data->City_;
    Capacity_ = Data->Capacity_;
    Fullness_ = Data->Fullness_;
}

std::string BasicStorage::GetName() { return Name_; }

void BasicStorage::SetName(std::string &Name) { Name_ = Name; }

std::string BasicStorage::GetCity() { return City_; }

void BasicStorage::SetCity(std::string &City) { City_ = City; }

size_t BasicStorage::GetCapacity() { return Capacity_; }

void BasicStorage::SetCapacity(size_t Capacity) { Capacity_ = Capacity; }

size_t BasicStorage::GetFullness() { return Fullness_; }

void BasicStorage::SetFullness(size_t Fullness) { Fullness_ = Fullness; }

size_t BasicStorage::GetPercentage() { return std::ceil((static_cast<double>(Fullness_) / Capacity_) * 100); }
