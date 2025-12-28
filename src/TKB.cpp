#include "TKB.h"
#include <iostream>
#include <fstream>
#include <sstream>

SubjectTable::SubjectTable() {}

SubjectTable::SubjectTable(std::string _IDClass, std::string _CourseID, std::string _Name, std::string _DayOfWeek, std::string _Time, std::string _Place, std::string _TeacherName)
    : IDClass(_IDClass), CourseID(_CourseID), Name(_Name), DayOfWeek(_DayOfWeek), Time(_Time), Place(_Place), TeacherName(_TeacherName) {}

std::vector<SubjectTable> SubjectTable::readData(const std::string& filename) {
    std::vector<SubjectTable> subjects;
    std::ifstream file(filename); 
    if (!file.is_open()) {
        std::cerr << "Khong the mo file " << filename << std::endl;
        return subjects;
    }

    std::string line;
    while (getline(file, line)) { 
        if (line.empty()) continue;
        
        std::stringstream ss(line); 
        std::string IDClass, CourseID, Name, DayOfWeek, Time, Place, TeacherName;
        
        std::getline(ss, IDClass, ',');
        std::getline(ss, CourseID, ',');
        std::getline(ss, Name, ',');
        std::getline(ss, DayOfWeek, ',');
        std::getline(ss, Time, ',');
        std::getline(ss, Place, ',');
        std::getline(ss, TeacherName, ',');
        
        subjects.push_back(SubjectTable(IDClass, CourseID, Name, DayOfWeek, Time, Place, TeacherName));
    }

    file.close();
    return subjects;
}
