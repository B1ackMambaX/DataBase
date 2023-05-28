#include "iostream"
#include "Database.h"
using namespace std;





int main() {
    string stud;
    string group;
    string spec;
    cout << "Enter the path to students table: ";
    cin >> stud;
    cout << "Enter the path to groups table: ";
    cin >> group;
    cout << "Enter the path to spec table: ";
    cin >> spec;
    system("cls");

    Database DB(stud, group, spec);
    DB.UpdateStudents();
    DB.UpdateGroups();
    DB.UpdateSpec();
    while (true) {
        cout << "Available commands:" << endl
             << "1: Print Students Table" << endl
             << "2: Print Groups Table" << endl
             << "3: Print Specs Table " << endl
             << "4: Add Student" << endl
             << "5: Add Group" << endl
             << "6: Add Spec" << endl
             << "7: Find Student" << endl
             << "8: Change Student" << endl
             << "9: Delete Student" << endl
             << "10: Delete Group" << endl
             << "11: Delete Spec" << endl
             << "12: Create exam list" << endl
             << "13: Close app" << endl
             << "------------------------" << endl << endl;
        int x;
        cin >> x;
        if (x == 1) {
            system("cls");
            cout << "Students Table:" << endl << endl;
            DB.printStudents();
            cout << endl << endl;
            continue;
        }
        if (x == 2) {
            system("cls");
            cout << "Groups Table:" << endl << endl;
            DB.printGroups();
            cout << endl << endl;
            continue;
        }
        if (x == 3) {
            system("cls");
            cout << "Spec Table:" << endl << endl;
            DB.printSpecs();
            cout << endl << endl;
            continue;
        }
        if (x == 4) {
            string name, lastName, surname, dateOfBirth, group;
            system("cls");
            cout << "You`re adding a student" << endl << endl;
            cout << "Enter first name:";
            cin >> name;
            cout << "Enter last name:";
            cin >> lastName;
            cout << "Enter surname:";
            cin >> surname;
            cout << "Date of birth:";
            cin >> dateOfBirth;
            cout << "Enter group name:";
            cin >> group;
            if ((DB.findStudent(Database::StudentsTable(0, name, lastName, surname, dateOfBirth, DB.findGroup(group).id))).size() != 0) {
                system("cls");
                cout << "This student is already existing" << endl << endl;
            }
            else if (DB.findGroup(group).groupName == "null") {
                system("cls");
                cout << "Group of this student not found, add group firstly" << endl;
            }
            else {
                DB.AddStudent(name, lastName, surname, dateOfBirth, DB.findGroup(group).id);
                DB.UpdateStudents();
                system("cls");
                cout << "Student succesfully added" << endl << endl;
            }
            continue;
        }
        if (x == 5) {
            system("cls");
            string group, spec;
            cout << "You`re adding a group" << endl << endl;
            cout << "Enter group name:";
            cin >> group;
            cout << "Enter spec name:";
            cin >> spec;
            if (DB.findGroup(group).groupName != "null") {
                system("cls");
                cout << "This group is already existing" << endl << endl;
            }
            else if(DB.findSpec(spec).SpecName == "null") {
                cout << "Spec of group not found, add spec firstly" << endl;
            }
            else {
                DB.AddGroup(group, DB.findSpec(spec).id);
                system("cls");
                DB.UpdateGroups();
                cout << "Group succesfully added" << endl << endl;
            }
            continue;
        }
        if (x == 6) {
            system("cls");
            string items, spec;
            cout << "You`re adding a spec" << endl << endl;
            cout << "Enter spec name:";
            cin >> spec;
            cout << "Enter sitem list name:";
            cin >> items;
            if (DB.findSpec(spec).SpecName != "null") {
                system("cls");
                cout << "This spec is already existing" << endl << endl;
            }
            else {
                DB.AddSpec(spec, items);
                system("cls");
                DB.UpdateSpec();
                cout << "Spec succesfully added" << endl << endl;
            }
            continue;
        }
        if (x == 7) {
            system("cls");
            cout << "You`re finding students" << endl << endl;
            string name, lastname, surname, dateOfBirth, groupName;
            cout << "Enter first name:";
            cin >> name;
            if (name == "-") name = "default";
            cout << "Enter last name:";
            cin >> lastname;
            if (lastname == "-") lastname = "default";
            cout << "Enter surname:";
            cin >> surname;
            if (surname == "-") surname = "default";
            cout << "Date of birth:";
            cin >> dateOfBirth;
            if (dateOfBirth == "-") dateOfBirth = "default";
            cout << "Enter group name:";
            cin >> group;
            if (groupName == "-") groupName = "default";
            Database::StudentsTable searchTarget = Database::StudentsTable(0, name, lastname, surname, dateOfBirth, DB.findGroup(group).id);
            list <Database::StudentsTable> searchRes = DB.findStudent(searchTarget);
            if (searchRes.size() == 0) {
                system("clear");
                cout << "No such Student" << endl << endl;
            }
            else {
                for (auto j : searchRes) {
                    cout << j.firstname << '\t' << j.lastname << '\t' << j.surname << '\t' << j.dateOfBirth << endl;
                }
            }
            continue;
        }
        if(x == 8) {
            system("cls");
            cout << "You're changing student info" << endl;
            cout << "Enter params of change target" << endl;
            string name, lastname, surname, dateOfBirth, groupName;
            string newName, newLastname, newSurname, newDoB, newGroup;

            cout << "Enter first name:";
            cin >> name;
            cout << "Enter last name:";
            cin >> lastname;
            cout << "Enter surname:";
            cin >> surname;
            cout << "Date of birth:";
            cin >> dateOfBirth;
            cout << "Enter group name:";
            cin >> group;

            system("cls");
            cout << "Enter new params, if field not specified type '-'" << endl;
            cout << "Enter first name:";
            cin >> newName;
            if (newName == "-") newName = "";
            cout << "Enter last name:";
            cin >> newLastname;
            if (newLastname == "-") newLastname = "";
            cout << "Enter surname:";
            cin >> newSurname;
            if (newSurname == "-") newSurname = "";
            cout << "Date of birth:";
            cin >> newDoB;
            if (newDoB == "-") newDoB = "";
            cout << "Enter group name:";
            cin >> newGroup;
            if (newGroup == "-") newGroup = group;

            Database::StudentsTable searchTarget(-1, name, lastname, surname, dateOfBirth, DB.findGroup(group).id);
            Database::StudentsTable NewInfo(-1, newName, newLastname, newSurname, newDoB, DB.findGroup(newGroup).id);
            system("cls");
            DB.changeStudent(searchTarget, NewInfo);
            DB.UpdateStudents();
            cout << "Student successfully changed" << endl;
            continue;

        }
        if (x == 9) {
            system("cls");
            cout << "You're deleting a student" << endl;
            cout << "Enter params of delete target" << endl;
            string name, lastname, surname, dateOfBirth, groupName;

            cout << "Enter first name:";
            cin >> name;
            cout << "Enter last name:";
            cin >> lastname;
            cout << "Enter surname:";
            cin >> surname;
            cout << "Date of birth:";
            cin >> dateOfBirth;
            cout << "Enter group name:";
            cin >> groupName;
            Database::StudentsTable searchTarget(-1, name, lastname, surname, dateOfBirth, DB.findGroup(groupName).id);
            system("cls");
            if(DB.deleteStudent(searchTarget)) {
                DB.UpdateStudents();
                cout << "Student successfully deleted" << endl;
            }
            else {
                cout << "Exception on deleting, check params" << endl;
            }
            continue;
        }

        if(x == 10) {
            system("cls");
            cout << "You're deleting a group" << endl;
            cout << "Enter the deleting target" << endl;
            string groupName;
            cin >> groupName;
            if(DB.deleteGroup(groupName)) {
                DB.UpdateGroups();
                cout << "Group successfully deleted" << endl;
            }
            else {
                cout << "Exception on deleting, check params" << endl;
            }
            continue;
        }
        if(x == 11) {
            system("cls");
            cout << "You're deleting a spec" << endl;
            cout << "Enter the deleting target" << endl;
            string specName;
            cin >> specName;
            if(DB.deleteSpec(specName)){
                DB.UpdateSpec();
                cout << "Spec successfully deleted" << endl;
            }
            else {
                cout << "Exception on deleting, check params" << endl;
            }
            continue;
        }
        if(x == 12) {
            system("cls");
            cout << "You're creating an exam list" << endl;
            cout << "Enter params of student" << endl;
            string name, lastname, surname, dateOfBirth, groupName;

            cout << "Enter first name:";
            cin >> name;
            cout << "Enter last name:";
            cin >> lastname;
            cout << "Enter surname:";
            cin >> surname;
            cout << "Date of birth:";
            cin >> dateOfBirth;
            cout << "Enter group name:";
            cin >> groupName;
            DB.createExamList(name,lastname,surname,dateOfBirth,groupName);
            system("cls");
            cout << "Exam list created" << endl;
            continue;
        }
        if (x == 13) {
            system("cls");
            cout << "Successfully closed" << endl;
            break;
        }
    }
}