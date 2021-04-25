// Copyright DimaZzZz101 2021


/*=====================Вариант 7=====================*/
/* БД: совокупность складов: одежда и обувь.         */
/* Информация: ID, Название, Город, Вместительность, */
/*             Заполненность, Резмеры обуви/одежды.  */
/* Сортировка: по названию склада (по алфавиту),     */
/*             по вместительности.                   */
/* Выборка (группировка): по загруженности (менее    */
/*                        чем на n% (n задается с    */
/*                        клавиатуры),               */
/*                        по городу.                 */

/*=================Функционал=================*/
/* Создание БД: однотипные и гибридные;       */
/* Вывод списка БД;                           */
/* Удаление БД                                */
/* Переименование БД                          */
/* Открытие БД                                */
/* Сохранение БД                              */
/* Добавить запись                            */
/* Редактировать запись                       */
/* Удаление записей                           */
/* Вывод записей                              */
/* Сортировка записей                         */
/* Выборка записей по правилу (значение поля) */
/* Сохранение выборки как новой БД            */

#include "include/DB.hpp"

bool IsOpen(DB *OpenedDB) {
    char Option = 'Y';

    if (OpenedDB != nullptr) {
        std::cout << "DataBase is opened, do you want to close it? Type (Y or N): ";
        std::cin >> Option;
        std::cin.ignore();
    }

    return Option == 'Y';
}

void StorageInfo(std::string Field, BasicStorage *Entry) {
    std::string Str = "";
    while (true) {
        std::cout << Field << std::endl;
        getline(std::cin, Str);
        std::vector<std::string> FieldData = PrepareString(Str);
        if (FieldData.size() == 0) continue;
        try {
            if (FieldData[0] == "exit") {
                break;
            }
            else if (FieldData[0] == "clear") {
                system("clear");
            }
            else if (FieldData[0] == "add") {
                Entry->Add(std::vector<std::string>(FieldData.begin() + 1, FieldData.end()));
            }
            else if (FieldData[0] == "remove") {
                Entry->Remove(std::vector<std::string>(FieldData.begin() + 1, FieldData.end()));
            }
            else if (FieldData[0] == "print") {
                Entry->Print();
            }
            else if (FieldData[0] == "edit" && FieldData.size() == 3) {
                if (FieldData[1] == "name")
                    Entry->SetName(FieldData[2]);
                else if (FieldData[1] == "city")
                    Entry->SetCity(FieldData[2]);
                else if (FieldData[1] == "capacity")
                    Entry->SetCapacity(stoi(FieldData[2]));
            }
            else if (FieldData[0] == "help") {
                std::cout   << "exit\n"
                            << "clear\n"
                            << "help\n"
                            << "add [type] [height] [size] [count] - for clothes\n"
                            << "remove [type] [height] [size] [count] - for clothes\n"
                            << "add [type] [size] [count] - for shoes\n"
                            << "remove [type] [size] [count] - for shoes\n"
                            << "print\n"
                            << "edit [name|city|capacity] [new name|new city|new capacity]\n";
            }
        }
        catch (const char *e) { std::cerr << e << std::endl; }

        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
    }
}

void Start() {
    DB *DataBase = nullptr;

    std::string Str = "";

    std::vector<BasicStorage *> GroupBySmth;

    while (true) {
        std::cout << "DB~" + (DataBase == nullptr ? "null" : DataBase->GetName()) + ": ";
        std::getline(std::cin, Str);
        std::vector<std::string> Data = PrepareString(Str);
        if (Data.size() == 0) continue;

        // Блок обработки комманд
        try {
            //==========================================================================================================
            // Остановка работы с БД
            if (Data[0] == "exit") {
                if (IsOpen(DataBase)) break;
            }
            //==========================================================================================================
            // Создание и открытие БД
            else if ((Data[0] == "create" && Data.size() == 3) || (Data[0] == "open" && Data.size() == 2)) {
                if (IsOpen(DataBase)) {
                    if (DataBase != nullptr) {
                        delete DataBase;
                        DataBase = nullptr;
                    }

                    if (Data[0] == "open") {
                        DataBase = new DB(Data[1] + ".db");
                    } else if (Data[0] == "create") {
                        DataBase = new DB(Data[1], (Data[2] == "shoes" ? 2 : Data[2] == "clothes"));
                    }
                }
            }
            //==========================================================================================================
            // Добавление записей в БД
            else if (Data[0] == "add") {
                BasicStorage *NewNode = nullptr;
                // Гибридная БД
                if (DataBase->GetDBType() == 0 && Data.size() == 5) {
                    if (Data[1] == "shoes") {
                        NewNode = new ShoesStorage(Data[2], Data[3], std::stoi(Data[4]));
                    } else if (Data[1] == "clothes") {
                        NewNode = new ClothesStorage(Data[2], Data[3], std::stoi(Data[4]));
                    } else throw "Unknown type";
                // БД склада одежды
                } else if (DataBase->GetDBType() == 1 && Data.size() == 4) {
                    NewNode = new ClothesStorage(Data[1], Data[2], std::stoi(Data[3]));
                // БД склада обуви
                } else if (DataBase->GetDBType() == 2 && Data.size() == 2) {
                    NewNode = new ShoesStorage(Data[1], Data[2], std::stoi(Data[3]));
                }

                DataBase->Add(NewNode);
            }
            //==========================================================================================================
            // Удаление записей из БД
            else if (Data[0] == "erase" && Data.size() == 2) {
                if (DataBase != nullptr) {
                    DataBase->Remove(Data[1]);
                }
            }
            //==========================================================================================================
            // Вывод информации из БД
            else if (Data[0] == "print") {
                if (Data.size() == 1) {
                    DataBase->Print();
                } else {
                    auto Node = DataBase->FindNode(Data[1]);
                    if (Node == nullptr) throw "Storage not found";
                    Node->Print();
                }
            }
            //==========================================================================================================
            // Группировка записей
            else if (Data[0] == "group") {
                // Группировка
                if (Data[1] == "by" && Data.size() == 4) {
                    if (Data[2] == "percent") {
                        GroupBySmth = DataBase->GroupByPercentage(std::stoi(Data[3]));
                    }
                    else if (Data[2] == "city") {
                        GroupBySmth = DataBase->GroupByCity(Data[3]);
                    }
                    else throw "Unidentified param";

                    std::cout << "Made up group from " << GroupBySmth.size() << " elements\n";
                }
                // Сохранение групы
                else if (Data[1] == "save" && Data.size() == 3) {
                    if (GroupBySmth.empty()) throw "Group is empty";

                    DB *NewDB = new DB(Data[2], DataBase->GetDBType(), GroupBySmth);
                    NewDB->SaveFile();
                    GroupBySmth.clear();
                    delete NewDB;
                }
                // Вывод выборки
                else if (Data[1] == "print") {
                    if (GroupBySmth.empty()) {
                        std::cout << "Group is empty\n";
                    }

                    for (auto Node : GroupBySmth) {
                        Node->Print();
                    }
                } else throw "Unknown command";
            }
            //==========================================================================================================
            // Сортировка БД
            else if (Data[0] == "sort") {
                if (!(Data.size() == 3 || Data.size() == 4)) throw "Something is wrong";

                bool Descending = Data[2] == "des"; // Сортировка по убыванию

                DataBase->Sort(Data[2 + Descending], Descending);
            }
            //==========================================================================================================
            // Поиск по названию
            else if (Data[0] == "find") {
                BasicStorage *Node = DataBase->FindNode(Data[1]);
                if (Node != nullptr) {
                    StorageInfo("DB~" + DataBase->GetName() + "~" + Node->GetName() + ": ", Node);
                } else throw "Storage not found";
            }
            //==========================================================================================================
            // Сохранение БД
            else if (Data[0] == "save") {
                if (DataBase != nullptr) {
                    DataBase->SaveFile((Data.size() == 2 ? Data[1] : "\0"));
                } else throw "No open DB";
            }
            //==========================================================================================================
            // Показ всех БД
            else if (Data[0] == "show") {
                for (auto i : fs::directory_iterator(fs::current_path())) {
                    if (i.path().extension() == ".db") {
                        std::cout << i.path().stem() << std::endl;
                    }
                }
            }
            //==========================================================================================================
            // Переименование БД
            else if (Data[0] == "rename") {
                if (DataBase == nullptr && Data.size() == 2) throw "No open DB";

                if (DataBase != nullptr && Data.size() == 2) {
                    Data.insert(Data.begin() + 1, DataBase->GetName());
                }
                fs::rename(fs::current_path().string() + "/" + Data[1] + ".db",
                           fs::current_path().string() + "/" + Data[2] + ".db");
                if (DataBase != nullptr && Data[1] == DataBase->GetName()) {
                    DataBase->SetName(Data[2]);
                }
            }
            //==========================================================================================================
            // Удаление БД
            else if (Data[0] == "remove") {
                // Конструкция, аналогичная rename
                if (Data.size() == 1 && DataBase == nullptr) throw "No open DB";
                if (Data.size() == 1) {
                    Data.push_back(DataBase->GetName());
                }
                fs::remove(fs::current_path().string() + "/" + Data[1] + ".db");
                if (DataBase != nullptr && Data[1] == DataBase->GetName()) {
                    delete DataBase;
                    DataBase = nullptr;
                }
            }
            //==========================================================================================================
            // Очистка консольного окна
            else if (Data[0] == "clear") {
                system("clear");
            }
            //==========================================================================================================
            // Закрытие БД
            else if (Data[0] == "close") {
                if (DataBase == nullptr) throw "No open DBs";
                if (IsOpen(DataBase)) {

                    delete DataBase;
                    DataBase = nullptr;
                }
            }
            //==========================================================================================================
            else if (Data[0] == "help") {
                std::cout   << "exit\n"
                            << "clear\n"
                            << "close\n"
                            << "help\n"
                            << "create [name] [hybrid|shoes|clothes]\n"
                            << "open [name]\n"
                            << "show\n"
                            << "print\n"
                            << "print [name]\n"
                            << "add [name] [city] [capacity]\n"
                            << "add [shoes|clothes] [name] [city] [capacity]\n"
                            << "erase [name]\n"
                            << "remove\n"
                            << "remove [name]\n"
                            << "get [name]\n"
                            << "save\n"
                            << "save [name]\n"
                            << "sort by [Name|Capacity]\n"
                            << "sort by des [Name|capacity]\n"
                            << "group by [city|percent] [city name|percent]\n"
                            << "group save [name]\n"
                            << "group print\n"
                            << "rename [new name]\n"
                            << "rename [name] [new name]\n";
            }
            //==========================================================================================================
        }
        catch (const char *e) { std::cerr << e << std::endl; }

        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
    }
}

int main() {
    Start();
    return 0;
}
