#include <iostream>
#include "database.h"
#include <vector>
void split(std::string* arr, std::string data){
    int j = 0;
    std::string buff;
    for(int i = 0; i < data.size(); i++){
        if(data[i] == '\t'){
            arr[j] = buff;
            j++;
            buff = "";
        }
        else{
            buff += data[i];
        }
    }
    arr[j] = buff;
}

Database::Database(std::string firstPath, std::string secondPath, std::string thirdPath) {
    this->studPath = firstPath;
    this->groupPath = secondPath;
    this->specPath = thirdPath;
}

void Database::UpdateStudents() {
    std::ofstream out(studPath);
    for(auto row = StudentsDataHolder.begin(); row != StudentsDataHolder.end(); row++ ){
        out << row->id << '\t' << row->firstname << '\t' << row->lastname << '\t' << row->surname << '\t'
            << row->dateOfBirth << '\t' << row->id_group << std::endl;
    }
    out.close();
    StudentsDataHolder.clear();
}

void Database::AddStudent(int id, std::string firstname, std::string lastname, std::string surname, std::string dateOfBirth, int id_group) {
    StudentsDataHolder.push_back(StudentsTable(id, firstname, lastname, surname, dateOfBirth, id_group));
}

void Database::AddGroup(int id, std::string groupName, int spec_id) {
    GroupsDataHolder.push_back(GroupsTable(id, groupName, spec_id));
}

void Database::UpdateGroups() {
    std::ofstream out(groupPath);
    for(auto row = GroupsDataHolder.begin(); row != GroupsDataHolder.end(); row++ ){
        out << row->id << '\t' << row->groupName << '\t' << row->spec_id <<  std::endl;
    }
    out.close();
    GroupsDataHolder.clear();
}

void Database::AddSpec(int id, std::string specName, std::string itemList) {
    SpecDataHolder.push_back(SpecTable(id, specName, itemList));
}

void Database::UpdateSpec() {
    std::ofstream out(specPath);
    for(auto row = SpecDataHolder.begin(); row != SpecDataHolder.end(); row++ ){
        out << row->id << '\t' << row->SpecName << '\t' << row->itemList << '\t' << std::endl;
    }
    out.close();
    SpecDataHolder.clear();
}

void Database::LoadStudents() {
    std::ifstream in(studPath);
    std::string buff;
    while(getline(in, buff)){
        std::string arr[6];
        split(arr, buff);
        StudentsDataHolder.push_back(StudentsTable(std::stoi(arr[0]), arr[1], arr[2], arr[3], arr[4], std::stoi(arr[5])));
    }
    in.close();
}

void Database::LoadGroups() {
    std::ifstream in(studPath);
    std::string buff;
    while(getline(in, buff)){
        std::string arr[3];
        split(arr, buff);
        GroupsDataHolder.push_back(GroupsTable(std::stoi(arr[0]), arr[1], std::stoi(arr[2])));
    }
    in.close();
}

void Database::LoadSpec() {
    std::ifstream in(studPath);
    std::string buff;
    while(getline(in, buff)){
        std::string arr[3];
        split(arr, buff);
        SpecDataHolder.push_back(SpecTable(std::stoi(arr[0]), arr[1], arr[2]));
    }
    in.close();
}

std::list<Database::StudentsTable> Database::findStudent(Database:: StudentsTable searchTarget) {
    std::list<StudentsTable> searchResults;
    for(auto row = StudentsDataHolder.begin(); row != StudentsDataHolder.end(); row++){
        if(row->firstname == searchTarget.firstname || searchTarget.firstname == "default"
                && row->lastname == searchTarget.lastname || searchTarget.lastname == "default"
                && row->dateOfBirth == searchTarget.dateOfBirth || searchTarget.dateOfBirth == "default"
                && row->surname == searchTarget.surname || searchTarget.surname == "default"){
            searchResults.push_back(*row);
        }
    }
    return searchResults;
}

Database::GroupsTable Database::findGroup(std::string searchTarget) {
    for(auto row = GroupsDataHolder.begin(); row != GroupsDataHolder.end(); row++){
        if(row->groupName == searchTarget){
            return *row;
        }
    }
}

Database::SpecTable Database::findSpec(std::string searchTarget) {
    for(auto row = SpecDataHolder.begin(); row != SpecDataHolder.end(); row++){
        if(row->SpecName == searchTarget){
            return *row;
        }
    }
}

Database::SpecTable::SpecTable(int id, std::string specName, std::string itemList) {
    this->id = id;
    this->SpecName = specName;
    this->itemList = itemList;
}

Database::GroupsTable::GroupsTable(int id, std::string groupName, int spec_id) {
    this->id = id;
    this->groupName = groupName;
    this->spec_id = spec_id;
}

Database::StudentsTable::StudentsTable(int id, std::string firstname, std::string lastname, std::string surname,
                                       std::string dateOfBirth, int id_group) {
    this->id = id;
    this->id_group = id_group;
    this->lastname = lastname;
    this->firstname = firstname;
    this->surname = surname;
    this->dateOfBirth =dateOfBirth;
}


