#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    string name;
    int marks[5]; // BM, ENG, MATH, SCI, HIS
    float percentage;
    char overallGrade;
};

extern const int CLASS_COUNT;
extern vector<Student> classes[];

string getGradeStr(int mark);
char getGrade(float percent);
int inputMark(const string &subject);
void calculateResults(Student &s);
void saveToFile(int classIndex);
void loadFromFile(int classIndex);
int selectClass();
void menu(int classIndex);

#endif
