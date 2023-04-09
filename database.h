#pragma once

#include <string>
#include <list>
#include <fstream>

class Database {
private:
    //Пути где хранится файл таблицы
    std::string studPath;
    std::string groupPath;
    std::string specPath;
    //Глобальные айдишники для связи таблиц
    int IDStudents = 0;
    int IDGroups = 0;
    int IDSpec = 0;
    //Структуры для строк различных таблиц
    struct StudentsTable {
        int id;
        std::string firstname;
        std::string lastname;
        std::string surname;
        std::string dateOfBirth;
        int id_group;
        StudentsTable(int id, std::string firstname, std::string lastname, std::string surname,
            std::string dateOfBirth, int id_group);
    };
    struct GroupsTable {
        int id;
        std::string groupName;
        int spec_id;
        GroupsTable(int id, std::string groupName, int spec_id);
    };
    struct SpecTable {
            int id;
            std::string itemList;
            std::string SpecName;
            SpecTable(int id, std::string SpecName, std::string itemList);
        };
    //Буферы для выгрузки таблиц в ОП
    std::list<StudentsTable> StudentsDataHolder;
    std::list<GroupsTable> GroupsDataHolder;
    std::list<SpecTable> SpecDataHolder;
public:
    Database(std::string firstPath, std::string secondPath, std::string thirdPath);
    //Методы для выгрузки таблиц из файлов
    void LoadStudents();
    void LoadGroups();
    void LoadSpec();
    //Методы для обновления таблиц(выгружаем из ОП и записываем в файл)
     void UpdateStudents();
     void UpdateGroups();
     void UpdateSpec();
    //Методы для добавления новых записей в ДатаХолдеры
    void AddStudent(int id, std::string firstname, std::string lastname, std::string surname, std::string dateOfBirth, int id_group);
    void AddGroup(int id, std::string groupName, int spec_id);
    void AddSpec(int id, std::string specName, std::string itemList);
    //Методы для поиска по таблицам
    std::list<StudentsTable> findStudent(StudentsTable searchTarget);
    GroupsTable findGroup(std::string searchTarget);
    SpecTable findSpec(std::string searchTarget);
};

void split(std::string* arr, std::string data);
