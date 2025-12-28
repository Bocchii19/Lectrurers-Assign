#include "GV.h"
#include <iostream>
#include <fstream>
#include <sstream>

Teacher::Teacher() : assignedCount(0) {}

Teacher::Teacher(std::string _Name, std::vector<std::string> _Subjects, std::string _telNum)
    : Name(_Name), Subjects(_Subjects), telNum(_telNum), assignedCount(0) {}

std::vector<Teacher> Teacher::readData(const std::string& filename) {
    std::vector<Teacher> teachers;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Loi: Khong the mo file " << filename << std::endl;
        return teachers;
    }

    std::string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string Name, telNum, Sub1, Sub2;
        
        std::getline(ss, Name, ',');
        std::getline(ss, telNum, ',');
        std::getline(ss, Sub1, ',');
        std::getline(ss, Sub2, ',');

        std::vector<std::string> subjectList;
        if (!Sub1.empty()) subjectList.push_back(Sub1);
        if (!Sub2.empty() && Sub2 != "\r") subjectList.push_back(Sub2);

        teachers.push_back(Teacher(Name, subjectList, telNum));
    }

    file.close();
    return teachers;
}
