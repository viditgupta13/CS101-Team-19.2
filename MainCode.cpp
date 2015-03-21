#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
class Akinator
{
public:
    string characters[7][5]={{"SI No", "Name", "Department", "Gender", "State"}, {"1.", "Illa", "Aero", "Female", "Delhi"}, {"2.", "Vidit", "Meta", "Male", "UP"}, {"3.", "DK", "Aero", "Male", "UP"}, {"4.", "Nitya", "Aero", "Female", "Haryana"}, {"5.", "Bablu", "Aero", "Male", "Haryana"}, {"6.", "Shinjan", "Meta", "Male", "Delhi"}};
    string questions[4][3]={{"SI. No.", "Question", "YESCODE"}, {"1.", "Is the department of your character ", ""}, {"2.", "Is your character ", ""}, {"3.", "Is your character from ", "2"}};
    string code[4]={"", "", "2 1 ", "3 "};//notice the spaces given at the end of 3. first entry will be blank. in test code no children for department question
    int n;
    int index;//index is a variable which will point to the parent question. the parent question points to the children from code array
    Akinator()
    {
        n=7;
        index=3;
    }
