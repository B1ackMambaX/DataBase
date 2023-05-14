#pragma once

#include <string>
#include <list>
#include <set>
#include <fstream>

class Database {
public:
    //Структуры для строк различных таблиц
    struct StudentsTable;
    struct GroupsTable;
    struct SpecTable;
private:
    //Пути где хранится файл таблицы
    std::string studPath;
    std::string groupPath;
    std::string specPath;
    //Глобальные айдишники для связи таблиц
    int IDStudents = 0;
    int IDGroups = 0;
    int IDSpec = 0;
    //Буферы для выгрузки таблиц в ОП
    std::set<StudentsTable> StudentsDataHolder;
    std::set<GroupsTable> GroupsDataHolder;
    std::set<SpecTable> SpecDataHolder;
public:

    struct StudentsTable {
        int id;
        std::string firstname;
        std::string lastname;
        std::string surname;
        std::string dateOfBirth;
        int id_group;
        StudentsTable(int id, std::string firstname, std::string lastname, std::string surname,
                      std::string dateOfBirth, int id_group);
        StudentsTable() {};
        bool operator<(const StudentsTable& T) const {
            return id < T.id;
        }
    };
    struct GroupsTable {
        int id;
        std::string groupName;
        int spec_id;
        GroupsTable(int id, std::string groupName, int spec_id);
        bool operator<(const GroupsTable& T) const {
            return id < T.id;
        }
        GroupsTable() {};
    };
    struct SpecTable {
        int id;
        std::string itemList;
        std::string SpecName;
        SpecTable(int id, std::string SpecName, std::string itemList);
        bool operator<(const SpecTable& T) const {
            return id < T.id;
        }
        SpecTable() {};
    };
    Database(std::string firstPath, std::string secondPath, std::string thirdPath);
    //Методы для выгрузки таблиц из файлов
    //void LoadStudents();// deprecated, rework
    //void LoadGroups();// deprecated, rework
    //void LoadSpec();// deprecated, rework

    //Методы для обновления таблиц(выгружаем из ОП и записываем в файл)
    void UpdateStudents();// Need update (done)
    void UpdateGroups();// Need update (done)
    void UpdateSpec();// Need update (done)
    //Методы для добавления новых записей в ДатаХолдеры
    void AddStudent(std::string firstname, std::string lastname, std::string surname, std::string dateOfBirth, int id_group);
    void AddGroup(std::string groupName, int spec_id);
    void AddSpec(std::string specName, std::string itemList);
    //Методы для поиска по таблицам
    std::list<StudentsTable> findStudent(StudentsTable searchTarget); // fixed
    GroupsTable findGroup(std::string groupname); // fixed
    SpecTable findSpec(std::string specname); // fixed

    //Изменение записей
    void changeStudent(StudentsTable searchTarget, StudentsTable newinfo);

    //Вывод в консоль таблиц
    void printStudents();
    void printGroups();
    void printSpecs();
};

void split(std::string* arr, std::string data); // rework
