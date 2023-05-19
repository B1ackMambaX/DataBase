#include "iostream"
#include "database.h"
#include "stdio.h"
using namespace std;





int main() {
    string stud;
    string group;
    string spec;
    cout << "Enter the names of tables" << endl;
    cin >> stud >> group >> spec;
    system("cls");

    Database DB(stud, group, spec);
    DB.UpdateStudents();
    DB.UpdateGroups();
    DB.UpdateSpec();
    while (true) {
        cout << "Avialable commands:" << endl
             << "1: Print Students Table" << endl
             << "2: Print Groups Table" << endl
             << "3: Print Specs Table " << endl
             << "4: Add Student" << endl
             << "5: Add Group" << endl
             << "6: Add Spec" << endl
             << "7: Find Student" << endl
             << "8: Change Student" << endl
             << "9: Close app" << endl
             << "------------------------" << endl << endl;
        char x = getchar();
        if (x == '1') {
            system("cls");
            cout << "Students Table:" << endl << endl;
            DB.printStudents();
            cout << endl << endl;
        }
        if (x == '2') {
            system("cls");
            cout << "Groups Table:" << endl << endl;
            DB.printGroups();
            cout << endl << endl;
        }
        if (x == '3') {
            system("cls");
            cout << "Spec Table:" << endl << endl;
            DB.printSpecs();
            cout << endl << endl;
        }
        if (x == '4') {
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
            else {
                DB.AddStudent(name, lastName, surname, dateOfBirth, DB.findGroup(group).id);
                DB.UpdateStudents();
                system("cls");
                cout << "Student succesfully added" << endl << endl;
            }

        }
        if (x == '5') {
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
            else {
                DB.AddGroup(group, DB.findSpec(spec).id);
                system("cls");
                DB.UpdateGroups();
                cout << "Group succesfully added" << endl << endl;
            }

        }
        if (x == '6') {
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

        }
        if (x == '7') {
            system("clear");
            cout << "You`re finding students" << endl << endl;
            string name, lastname, surname, dateOfBirth, groupName;
            cout << "Enter first name:";
            cin >> name;
            if (name == "-") name == "default";
            cout << "Enter last name:";
            cin >> lastname;
            if (lastname == "-") lastname == "default";
            cout << "Enter surname:";
            cin >> surname;
            if (surname == "-") surname == "default";
            cout << "Date of birth:";
            cin >> dateOfBirth;
            if (dateOfBirth == " ") dateOfBirth == "default";
            cout << "Enter group name:";
            cin >> group;
            if (groupName == "-") groupName == "default";
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

        }
        if (x == '9') {
            system("cls");
            cout << "Successfully closed" << endl;
            break;
        }
    }
}