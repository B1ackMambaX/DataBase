#include "iostream"
#include "database.h"
using namespace std;

int main() {
    Database Test("Students.txt", "", "");
    Test.LoadStudents();
}