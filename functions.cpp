#include "functions.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

const int CLASS_COUNT = 4;
vector<Student> classes[CLASS_COUNT];
string filenames[CLASS_COUNT] = {"class_A.csv", "class_B.csv", "class_C.csv", "class_D.csv"};

string getGradeStr(int mark) {
    if (mark >= 90) return "A+";
    if (mark >= 80) return "A";
    if (mark >= 70) return "A-";
    if (mark >= 65) return "B+";
    if (mark >= 60) return "B";
    if (mark >= 55) return "C+";
    if (mark >= 50) return "C";
    if (mark >= 45) return "D";
    if (mark >= 40) return "E";
    return "G";
}

char getGrade(float percent) {
    if (percent >= 70) return 'A';
    if (percent >= 60) return 'B';
    if (percent >= 50) return 'C';
    if (percent >= 45) return 'D';
    if (percent >= 40) return 'E';
    return 'F';
}

int inputMark(const string &subject) {
    int mark;
    do {
        cout << subject << ": ";
        cin >> mark;
        if (mark < 0 || mark > 100) {
            cout << "Invalid input! Please enter a mark between 0 and 100.\n";
        }
    } while (mark < 0 || mark > 100);
    return mark;
}

void calculateResults(Student &s) {
    int total = 0;
    for (int i = 0; i < 5; ++i) total += s.marks[i];
    s.percentage = total / 5.0;
    s.overallGrade = getGrade(s.percentage);
}

void saveToFile(int classIndex) {
    sort(classes[classIndex].begin(), classes[classIndex].end(), [](const Student &a, const Student &b) {
        return a.name < b.name;
    });

    ofstream file(filenames[classIndex]);
    for (const auto &s : classes[classIndex]) {
        file << s.name;
        for (int i = 0; i < 5; ++i)
            file << "," << s.marks[i];
        file << "\n";
    }
    file.close();
}

void loadFromFile(int classIndex) {
    classes[classIndex].clear();
    ifstream file(filenames[classIndex]);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Student s;
        getline(ss, s.name, ',');
        for (int i = 0; i < 5; ++i) {
            string mark;
            getline(ss, mark, ',');
            s.marks[i] = stoi(mark);
        }
        calculateResults(s);
        classes[classIndex].push_back(s);
    }
    file.close();
}

int selectClass() {
    int choice;
    cout << "\nSelect Class:\n1. A\n2. B\n3. C\n4. D\nChoice: ";
    cin >> choice;
    return choice - 1; // array index from 0
}

void menu(int classIndex) {
    while (true) {
        system("CLS"); // clear screen, Windows only
        cout << "\n1. Register a New Student\n2. Update Student Marks\n3. View Student Marks\n4. Switch Student’s Class\n5. Close the Program\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        system("CLS");
        switch (choice) {
            case 1: {
                Student s;
                cout << "Enter student name: ";
                getline(cin, s.name);
                s.marks[0] = inputMark("BM");
                s.marks[1] = inputMark("ENG");
                s.marks[2] = inputMark("MATH");
                s.marks[3] = inputMark("SCI");
                s.marks[4] = inputMark("HIS");
                calculateResults(s);
                classes[classIndex].push_back(s);
                saveToFile(classIndex);
                break;
            }
            case 2: {
                if (classes[classIndex].empty()) {
                    cout << "No students in this class.\n";
                    system("pause");
                    break;
                }

                cout << "\nClass " << char('A' + classIndex) << " - List of students:\n";
                for (size_t i = 0; i < classes[classIndex].size(); ++i) {
                    cout << i + 1 << ". " << classes[classIndex][i].name << "\n";
                }

                string input;
                cout << "Enter the number of the student to modify (or 'c' to cancel): ";
                cin >> input;
                if (input == "c" || input == "C") {
                    cout << "Modification canceled.\n";
                    system("pause");
                    break;
                }

                int choice = stoi(input);
                if (choice < 1 || choice > (int)classes[classIndex].size()) {
                    cout << "Invalid choice.\n";
                    system("pause");
                    break;
                }

                Student &s = classes[classIndex][choice - 1];

                cout << "Enter new marks for " << s.name << ":\n";
                s.marks[0] = inputMark("BM");
                s.marks[1] = inputMark("ENG");
                s.marks[2] = inputMark("MATH");
                s.marks[3] = inputMark("SCI");
                s.marks[4] = inputMark("HIS");

                calculateResults(s);
                saveToFile(classIndex);
                cout << "Marks updated for " << s.name << "!\n";
                system("pause");
                break;
            }
            case 3: {
                if (classes[classIndex].empty()) {
                    cout << "No students to display.\n";
                    system("pause");
                    break;
                }

                vector<Student> ranked = classes[classIndex];
                sort(ranked.begin(), ranked.end(), [](const Student &a, const Student &b) {
                    return a.percentage > b.percentage;
                });

                cout << "\nClass " << char('A' + classIndex) << "\n";
                cout << left << setw(4) << "No" << setw(15) << "Name"
                     << setw(6) << "BM" << setw(4) << "GR"
                     << setw(6) << "ENG" << setw(4) << "GR"
                     << setw(6) << "MATH" << setw(4) << "GR"
                     << setw(6) << "SCI" << setw(4) << "GR"
                     << setw(6) << "HIS" << setw(4) << "GR"
                     << setw(10) << "%" << setw(6) << "GR"
                     << setw(6) << "Rank" << endl;

                for (size_t i = 0; i < ranked.size(); ++i) {
                    const Student &s = ranked[i];
                    cout << left << setw(4) << i + 1 << setw(15) << s.name;
                    for (int j = 0; j < 5; ++j) {
                        cout << setw(6) << s.marks[j] << setw(4) << getGradeStr(s.marks[j]);
                    }
                    cout << setw(10) << s.percentage << setw(6) << s.overallGrade << setw(6) << i + 1 << endl;
                }
                system("pause");
                break;
            }

            case 4:
                return;
            case 5:
                exit(0);
            default:
                cout << "Invalid choice.\n";
        }
    }
}
