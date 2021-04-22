// Copyright DimaZzZz101 2021

#include "../include/DB.hpp"

DB::DB(std::string &DBName, size_t DataBaseType) : DBName_(DBName), DataBaseType_(DataBaseType) {}

DB::DB(std::string &DBName, size_t DataBaseType, std::vector<BasicStorage *> &Data)
        : DBName_(DBName), DataBaseType_(DataBaseType) {
    for (auto it : Data) {
        if (auto Shoes_Storage = dynamic_cast<ShoesStorage *>(it)) {
            GeneralData_.push_back(new ShoesStorage(Shoes_Storage));

        } else if (auto Clothes_Storage = dynamic_cast<ClothesStorage *>(it)) {
            GeneralData_.push_back(new ClothesStorage(Clothes_Storage));
        }
    }
}

DB::DB(std::string PATH) {
    std::ifstream Input(PATH);
    if (Input.is_open()) {
        std::stringstream ss;
        ss << Input.rdbuf();
        std::vector<std::string> FromInput = PrepareString(ss.str(), "###\n");
        Input.close();

        std::vector<std::string> Data = PrepareString(FromInput[0], "\n");
        DBName_ = Data[0];
        DataBaseType_ = std::stoi(Data[1]);

        for (size_t i = 1; i < FromInput.size(); ++i) {
            if (FromInput[i][0] == 'C')
                GeneralData_.push_back(new ClothesStorage(FromInput[i].substr(2)));
            else if (FromInput[i][0] == 'S')
                GeneralData_.push_back(new ShoesStorage(FromInput[i].substr(2)));
        }
    } else throw std::invalid_argument("Invalid PATH");
}

std::string DB::GetName() { return DBName_; }

void DB::SetName(std::string &Name) { DBName_ = Name; }

size_t DB::GetDBType() { return DataBaseType_; }

void DB::SetDBType(size_t Type) { DataBaseType_ = Type; }

BasicStorage *DB::FindNode(std::string NodeName) {
    auto Node = std::find_if(GeneralData_.begin(), GeneralData_.end(),
                             [=](BasicStorage *item) { return item->GetName() == NodeName; });

    if (Node == GeneralData_.end()) return nullptr;
    else return *Node;
}

std::string DB::ToString() {
    std::stringstream ss;

    ss << GetName() << std::endl << DataBaseType_ << std::endl;

    for (auto Node : GeneralData_) ss << "###" << std::endl << Node->ToString();

    return ss.str();
}

void DB::Print() {
    std::cout << "Name: " << GetName() << std::endl << "Type: ";

    if (DataBaseType_ == 0) {
        std::cout << "Hybrid" << std::endl;
    } else if (DataBaseType_ == 1) {
        std::cout << "Clothes" << std::endl;
    } else {
        std::cout << "Shoes" << std::endl;
    }

    if(!GeneralData_.empty()) std::cout << "\nItems:\n\n";

    for (auto & item : GeneralData_) item->Print();
}

void DB::Add(BasicStorage *Node) {
    if (Node == nullptr) throw "Node not found";

    if (FindNode(Node->GetName()) != nullptr) throw "Node already exists";

    GeneralData_.push_back(Node);
}

void DB::Remove(std::string &Name) {
    auto Node = FindNode(Name);

    if (Node == nullptr) throw "Not found";

    GeneralData_.erase(remove(GeneralData_.begin(), GeneralData_.end(), Node), GeneralData_.end());

    delete Node;
}

DB::~DB() {
    for (size_t i = 0; i < GeneralData_.size(); ++i) {
        delete GeneralData_[i];
    }

    GeneralData_.clear();
}

void DB::SaveFile(std::string Name) {
    if (Name == "\0") {
        std::ofstream Output(DBName_ + ".txt");
        Output << ToString();
        Output.close();
    } else {
        std::ofstream Output(Name + ".txt");
        Output << ToString();
        Output.close();
    }


}

//===Блок сортировки====================================================================================================
void DB::Sort(std::string Param, bool Type) {
    if (Param == "Name")
        sort(GeneralData_.begin(), GeneralData_.end(), (Type ? SortByNameDescending : SortByName));
    else if (Param == "Capacity")
        sort(GeneralData_.begin(), GeneralData_.end(), (Type ? SortByCapacityDescending : SortByCapacity));
    else throw "Wrong parametr";
}

bool DB::SortByName(BasicStorage *a, BasicStorage *b) { return a->GetName() < b->GetName(); }

bool DB::SortByNameDescending(BasicStorage *a, BasicStorage *b) { return a->GetName() > b->GetName(); }

bool DB::SortByCapacity(BasicStorage *a, BasicStorage *b) { return a->GetCapacity() < b->GetCapacity(); }

bool DB::SortByCapacityDescending(BasicStorage *a, BasicStorage *b) {
    return a->GetCapacity() > b->GetCapacity();
}


std::vector<BasicStorage *> DB::GroupByPercentage(const size_t Percentage) {
    std::vector<BasicStorage*> Group;

    for (auto Node : GeneralData_) {
        if ((Node->GetFullness() / Node->GetCapacity())*100 < Percentage) {
            Group.push_back(Node);
        }
    }

    return Group;
}

std::vector<BasicStorage *> DB::GroupByCity(const std::string &CityName) {
    std::vector<BasicStorage*> Group;

    for (auto Node : GeneralData_) {
        if (Node->GetCity() == CityName) {
            Group.push_back(Node);
        }
    }

    return Group;
}
