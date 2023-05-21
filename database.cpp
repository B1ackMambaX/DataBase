#include <iostream>
#include "database.h"
#include <vector>
#include <algorithm>
void split(std::string* arr, std::string data) {
    int j = 0;
    std::string buff;
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == '\t') {
            arr[j] = buff;
            j++;
            buff = "";
        }
        else {
            buff += data[i];
        }
    }
}

Database::Database(std::string firstPath, std::string secondPath, std::string thirdPath) {
    this->studPath = "Tables\\" + firstPath;
    this->groupPath = "Tables\\" + secondPath;
    this->specPath = "Tables\\" + thirdPath;
    if (firstPath != "") {
        std::fstream file(studPath);
        std::string temp;
        std::getline(file, temp);
        if (temp.size() != 0) {
            IDStudents = std::stoi(temp);
        }

        file.close();
    }
    if (secondPath != "") {
        std::fstream file(groupPath);
        std::string temp;
        std::getline(file, temp);
        if (temp.size() != 0) IDGroups = std::stoi(temp);
        file.close();
    }
    if (thirdPath != "") {
        std::fstream file(specPath);
        std::string temp;
        std::getline(file, temp);
        if (temp.size() != 0) IDSpec = std::stoi(temp);
        file.close();
    }


}



void Database::AddStudent(std::string firstname, std::string lastname, std::string surname, std::string dateOfBirth, int id_group) {
    StudentsDataHolder.insert(StudentsTable(IDStudents++, firstname, lastname, surname, dateOfBirth, id_group));
}
void Database::AddGroup(std::string groupName, int spec_id) {
    GroupsDataHolder.insert(GroupsTable(IDGroups++, groupName, spec_id));
}
void Database::AddSpec(std::string specName, std::string itemList) {
    SpecDataHolder.insert(SpecTable(IDSpec++, specName, itemList));
}

/*void Groups::update() {
    std::remove((filename + ".old").c_str());
    std::rename(filename.c_str(), (filename + ".old").c_str());
    std::string temp;
    std::ifstream filein(filename + ".old");
    std::ofstream fileout(filename);
    while (std::getline(filein, temp)) {
        int pos = 0;
        for (int i = 0; i < temp.size(); i++) {
            i++;
            pos++;
        }
        int Id = stoi(temp.substr(0, pos));
        int flag = -1;
        for (int i = 0; i < buff.size(); i++) {
            if (Id == buff[i].id) {
                flag = i;

                fileout << buff[flag].id << "\t" << buff[flag].group << "\t" << buff[flag].name << "\t" << buff[flag].info << "\t" << "\n";

                buff[i].id = -1;
                break;
            }
        }
        if (flag == -1) {
            fileout << temp << "\n";
        }

    }
    for (auto r : buff) {
        if (r.id != -1)
            fileout << r.id << "\t" << r.group << "\t" << r.name << "\t" << r.info << "\n";
    }
    buff.resize(0);
    filein.close();
    fileout.close();
}*/

void Database::UpdateSpec() {
    std::remove((specPath + ".old").c_str());
    std::rename(specPath.c_str(), (specPath + ".old").c_str());
    std::string temp;
    std::ifstream filein(specPath + ".old");
    std::ofstream fileout(specPath);
    fileout << IDSpec << std::endl;
    bool IsData = false;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        int Id = stoi(temp.substr(0, temp.find("\t")));
        int flag = -1;
        for (auto r : SpecDataHolder) {
            if (Id == r.id) {
                flag = 1;

                fileout << r.id << "\t" << r.SpecName << "\t" << r.itemList << "\t" << std::endl;

                r.id = -1;
                break;
            }
        }
        if (flag == -1) {
            fileout << temp << "\n";
        }

    }
    for (auto r : SpecDataHolder) {
        if (r.id != -1)
            fileout << r.id << "\t" << r.SpecName << "\t" << r.itemList << "\t" << std::endl;
    }
    SpecDataHolder.clear();
    filein.close();
    fileout.close();
}
void Database::UpdateStudents() {

    std::remove((studPath + ".old").c_str());
    std::rename(studPath.c_str(), (studPath + ".old").c_str());
    std::string temp;
    std::ifstream filein(studPath + ".old");
    std::ofstream fileout(studPath);
    fileout << IDStudents << std::endl;
    bool IsData = false;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        int Id = stoi(temp.substr(0, temp.find("\t")));
        int flag = -1;
        for (auto r : StudentsDataHolder) {
            if (Id == r.id) {
                flag = 1;

                fileout << r.id << '\t' << r.firstname << '\t' << r.lastname << '\t' << r.surname << '\t' << r.dateOfBirth << '\t' << r.id_group << '\t' << std::endl;
                StudentsDataHolder.erase(r);
                break;
            }
        }
        if (flag == -1) {
            fileout << temp << "\n";
        }

    }
    for (auto r : StudentsDataHolder) {
        fileout << r.id << '\t' << r.firstname << '\t' << r.lastname << '\t' << r.surname << '\t' << r.dateOfBirth << '\t' << r.id_group << '\t' << std::endl;
    }
    StudentsDataHolder.clear();
    filein.close();
    fileout.close();
}
void Database::UpdateGroups() {
    std::remove((groupPath + ".old").c_str());
    std::rename(groupPath.c_str(), (groupPath + ".old").c_str());
    std::string temp;
    std::ifstream filein(groupPath + ".old");
    std::ofstream fileout(groupPath);
    fileout << IDGroups << std::endl;
    bool IsData = false;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        int Id = stoi(temp.substr(0, temp.find("\t")));
        int flag = -1;
        for (auto r : GroupsDataHolder) {
            if (Id == r.id) {
                flag = 1;

                fileout << r.id << '\t' << r.groupName << '\t' << r.spec_id << '\t' << std::endl;

                r.id = -1;
                break;
            }
        }
        if (flag == -1) {
            fileout << temp << "\n";
        }

    }
    for (auto r : GroupsDataHolder) {
        if (r.id != -1)
            fileout << r.id << '\t' << r.groupName << '\t' << r.spec_id << '\t' << std::endl;
    }
    GroupsDataHolder.clear();
    filein.close();
    fileout.close();
}

/*
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
*/

std::list<Database::StudentsTable> Database::findStudent(Database::StudentsTable searchTarget) {
    if (StudentsDataHolder.size() != 0) {
        UpdateStudents();
    }
    std::list<StudentsTable> searchResults;
    std::ifstream filein(studPath);
    std::string temp;
    bool IsData = false;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        std::string row[6];
        split(row, temp);
        if ((row[1] == searchTarget.firstname || searchTarget.firstname == "default")
            && (row[2] == searchTarget.lastname || searchTarget.lastname == "default")
            && (row[3] == searchTarget.surname || searchTarget.surname == "default")
            && (row[4] == searchTarget.dateOfBirth || searchTarget.dateOfBirth == "default")
            && (stoi(row[5]) == searchTarget.id_group || searchTarget.id_group == -1)
            ) searchResults.push_back(StudentsTable(stoi(row[0]), row[1], row[2], row[3], row[4], stoi(row[5])));

    }
    return searchResults;
}

Database::GroupsTable Database::findGroup(std::string groupname) {
    if (GroupsDataHolder.size() != 0) {
        UpdateGroups();
    }
    std::ifstream filein(groupPath);
    std::string temp;
    bool IsData = false;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        std::string row[3];
        split(row, temp);
        if (row[1] == groupname) {
            return GroupsTable(stoi(row[0]), row[1], stoi(row[2]));
        }
    }
    std::string str = "null";
    return GroupsTable(-1, str, -1);
}

Database::SpecTable Database::findSpec(std::string specname) {

    if (SpecDataHolder.size() != 0) {
        UpdateSpec();
    }
    bool IsData = false;
    std::ifstream filein(specPath);
    std::string temp;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        std::string row[3];
        split(row, temp);
        if (row[1] == specname) {
            return SpecTable(stoi(row[0]), row[1], row[2]);
        }
    }
    return SpecTable(-1, "null", "null");
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

Database::StudentsTable::StudentsTable(int id, std::string firstname, std::string lastname, std::string surname, std::string dateOfBirth, int id_group) {
    this->id = id;
    this->id_group = id_group;
    this->lastname = lastname;
    this->firstname = firstname;
    this->surname = surname;
    this->dateOfBirth = dateOfBirth;
}

void Database::changeStudent(Database::StudentsTable searchTarget, Database::StudentsTable newinfo) {
    std::list<Database::StudentsTable> found = Database::findStudent(searchTarget);
    if (found.size() > 1) {
        std::cout << "Found more than 1 record\n";
        return;
    }
    if (found.size() == 0) {
        std::cout << "Not found\n";
        return;
    }
    auto it = StudentsDataHolder.find(searchTarget);
    if (it != StudentsDataHolder.end()) {
        StudentsDataHolder.erase(it);
    }
    StudentsTable temp;
    temp.id = found.front().id;

    if (newinfo.firstname == "") {
        temp.firstname = found.front().firstname;
    }
    else {
        temp.firstname = newinfo.firstname;
    }

    if (newinfo.lastname == "") {
        temp.lastname = found.front().lastname;
    }
    else {
        temp.lastname = newinfo.lastname;
    }

    if (newinfo.surname == "") {
        temp.surname = found.front().surname;
    }
    else {
        temp.surname = newinfo.surname;
    }

    if (newinfo.dateOfBirth == "") {
        temp.dateOfBirth = found.front().dateOfBirth;
    }
    else {
        temp.dateOfBirth = newinfo.dateOfBirth;
    }

    if (newinfo.id_group == -1) {
        temp.id_group = found.front().id_group;
    }
    else {
        temp.id_group = newinfo.id_group;
    }

    StudentsDataHolder.insert(temp);
    return;
}

void Database::printStudents() {
    std::ifstream filein(studPath);
    std::string temp;
    bool bFlag = false;
    while (std::getline(filein, temp)) {
        if (!bFlag) {
            bFlag = true;
            continue;
        }
        std::cout << temp;
        std::cout << std::endl << "-----------------------------------------------------------------------------------------" << std::endl;
    }
    filein.close();
}

void Database::printGroups() {
    std::ifstream filein(groupPath);
    std::string temp;
    bool bFlag = false;
    while (std::getline(filein, temp)) {
        if (!bFlag) {
            bFlag = true;
            continue;
        }
        std::cout << temp;
        std::cout << std::endl << "-----------------------------------------------------------------------------------------" << std::endl;
    }
    filein.close();
}

void Database::printSpecs() {
    std::ifstream filein(specPath);
    std::string temp;
    bool bFlag = false;
    while (std::getline(filein, temp)) {
        if (!bFlag) {
            bFlag = true;
            continue;
        }
        std::cout << temp.substr(2, temp.length());
        std::cout << std::endl << "-----------------------------------------------------------------------------------------" << std::endl;
    }
    filein.close();
}

bool Database::deleteStudent(StudentsTable searchTarget) {
    bool answer = 0;
    std::remove((studPath + ".old").c_str());
    std::rename(studPath.c_str(), (studPath + ".old").c_str());
    std::string temp;
    std::ifstream filein(studPath + ".old");
    std::ofstream fileout(studPath);
    fileout << IDStudents << std::endl;
    bool IsData = false;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        std::string row[6];
        split(row, temp);
        if ((row[1] == searchTarget.firstname)
            && (row[2] == searchTarget.lastname)
            && (row[3] == searchTarget.surname)
            && (row[4] == searchTarget.dateOfBirth)
            && (stoi(row[5]) == searchTarget.id_group)
            ) {
            answer = 1;
            continue;
        }
        fileout << temp << "\n";
    }
    auto it = StudentsDataHolder.begin();
    while (it != StudentsDataHolder.end()) {
        if ((it->firstname == searchTarget.firstname)
            && (it->lastname == searchTarget.lastname)
            && (it->surname == searchTarget.surname)
            && (it->dateOfBirth == searchTarget.dateOfBirth)
            && (it->id_group == searchTarget.id_group)) {
            StudentsDataHolder.erase(it++);
            answer = 1;
            break;
        }
        else {
            ++it;
        }
    }
    filein.close();
    fileout.close();
    return answer;
}

bool Database::deleteGroup(std::string groupname) {
    bool answer = 0;
    std::remove((groupPath + ".old").c_str());
    std::rename(groupPath.c_str(), (groupPath + ".old").c_str());
    std::string temp;
    std::ifstream filein(groupPath + ".old");
    std::ofstream fileout(groupPath);
    fileout << IDGroups << std::endl;
    bool IsData = false;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        std::string row[3];
        split(row, temp);
        if (row[1] == groupname) {
            answer = 1;
            continue;
        }
        fileout << temp << "\n";
    }
    auto it = GroupsDataHolder.begin();
    while (it != GroupsDataHolder.end()) {
        if (it->groupName == groupname) {
            GroupsDataHolder.erase(it++);
            answer = 1;
            break;
        }
        else {
            ++it;
        }
    }
    filein.close();
    fileout.close();
    return answer;
}

bool Database::deleteSpec(std::string specname) {
    bool answer = 0;
    std::remove((specPath + ".old").c_str());
    std::rename(specPath.c_str(), (specPath + ".old").c_str());
    std::string temp;
    std::ifstream filein(specPath + ".old");
    std::ofstream fileout(specPath);
    fileout << IDSpec << std::endl;
    bool IsData = false;
    while (std::getline(filein, temp)) {
        if (!IsData) {
            IsData = true;
            continue;
        }
        std::string row[3];
        split(row, temp);
        if (row[1] == specname) {
            answer = 1;
            continue;
        }
        fileout << temp << "\n";
    }
    auto it = SpecDataHolder.begin();
    while (it != SpecDataHolder.end()) {
        if (it->SpecName == specname) {
            SpecDataHolder.erase(it++);
            answer = 1;
            break;
        }
        else {
            ++it;
        }
    }
    filein.close();
    fileout.close();
    return answer;
}