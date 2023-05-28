#include <iostream>
#include "database.h"
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

database::database(std::string firstPath, std::string secondPath, std::string thirdPath) {
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



void database::AddStudent(std::string firstname, std::string lastname, std::string surname, std::string dateOfBirth, int id_group) {
    StudentsDataHolder.insert(StudentsTable(IDStudents++, firstname, lastname, surname, dateOfBirth, id_group));
}
void database::AddGroup(std::string groupName, int spec_id) {
    GroupsDataHolder.insert(GroupsTable(IDGroups++, groupName, spec_id));
}
void database::AddSpec(std::string specName, std::string itemList) {
    SpecDataHolder.insert(SpecTable(IDSpec++, specName, itemList));
}

void database::UpdateSpec() {
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
void database::UpdateStudents() {

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
void database::UpdateGroups() {
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

std::list<database::StudentsTable> database::findStudent(database::StudentsTable searchTarget) {
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

database::GroupsTable database::findGroup(std::string groupname) {
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

database::SpecTable database::findSpec(std::string specname) {

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
database::SpecTable database::findSpecById(int id) {

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
        if (stoi(row[0]) == id) {
            return SpecTable(stoi(row[0]), row[1], row[2]);
        }
    }
    return SpecTable(-1, "null", "null");
}

database::SpecTable::SpecTable(int id, std::string specName, std::string itemList) {
    this->id = id;
    this->SpecName = specName;
    this->itemList = itemList;
}

database::GroupsTable::GroupsTable(int id, std::string groupName, int spec_id) {
    this->id = id;
    this->groupName = groupName;
    this->spec_id = spec_id;
}

database::StudentsTable::StudentsTable(int id, std::string firstname, std::string lastname, std::string surname, std::string dateOfBirth, int id_group) {
    this->id = id;
    this->id_group = id_group;
    this->lastname = lastname;
    this->firstname = firstname;
    this->surname = surname;
    this->dateOfBirth = dateOfBirth;
}

void database::changeStudent(database::StudentsTable searchTarget, database::StudentsTable newinfo) {
    std::list<database::StudentsTable> found = database::findStudent(searchTarget);
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

void database::printStudents() {
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

void database::printGroups() {
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

void database::printSpecs() {
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

bool database::deleteStudent(StudentsTable searchTarget) {
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

bool database::deleteGroup(std::string groupname) {
    StudentsTable searchTarget(-1, "default", "default", "default", "default", findGroup(groupname).id);
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
        } else {
            ++it;
        }
    }
    std:: list changed  = database ::findStudent(searchTarget);
    if(changed.size() == 0) return answer;
    for(auto j : changed) {
        deleteStudent(j);
        AddStudent(j.firstname,j.lastname, j.surname, j.dateOfBirth, -1);
    }
    UpdateStudents();
    filein.close();
    fileout.close();
    return answer;
}

bool database::deleteSpec(std::string specname) {
    bool answer = 0;
    int id = findSpec(specname).id;
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
    filein.close();
    fileout.close();

    std::remove((groupPath + ".old").c_str());
    std::rename(groupPath.c_str(), (groupPath + ".old").c_str());
    std::string tempGroup;
    std::ifstream fileinG(groupPath + ".old");
    std::ofstream fileoutG(groupPath);
    fileoutG << IDGroups << std::endl;
    bool IsDataG = false;
    while (std::getline(fileinG, tempGroup)) {
        if (!IsDataG) {
            IsDataG = true;
            continue;
        }
        std::string row[3];
        split(row, tempGroup);
        if (stoi(row[2]) == id) {
            fileoutG << row[0] << '\t' << row[1] << '\t' << -1 << '\t' << '\n';
            continue;
        }
        fileoutG << tempGroup << "\n";
    }
    fileinG.close();
    fileoutG.close();
    return answer;
}

void database::createExamList(std::string name, std::string lastname, std::string surname, std::string DoB, std::string group) {
    StudentsTable searchTarget(-1, name, lastname, surname, DoB, findGroup(group).id);
    std::list<StudentsTable> found =  findStudent(searchTarget);
    if(found.size() != 1) {
        std::cout << "There are more than one or no students, check params" << std::endl;
        return;
    }
    std::ofstream fileout(found.back().firstname);
    fileout << found.back().firstname << '\t' << found.back().lastname << '\t' << found.back().surname << '\t' << found.back().dateOfBirth << '\t' << findGroup(group).groupName <<'\t' << findSpecById(
            findGroup(group).spec_id).SpecName << '\t' <<  findSpecById(findGroup(group).spec_id).itemList;
}
