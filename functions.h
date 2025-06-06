#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

struct Student {
    std::string name;
    int marks[5]; // BM, ENG, MATH, SCI, HIS
    float percentage;
    char overallGrade;
};

extern const int CLASS_COUNT;
extern std::vector<Student> classes[];

std::string getGradeStr(int mark);
char getGrade(float percent);
int inputMark(const std::string &subject);
void calculateResults(Student &s);
void saveToFile(int classIndex);
void loadFromFile(int classIndex);
int selectClass();
void menu(int classIndex);

#endif // FUNCTIONS_H
