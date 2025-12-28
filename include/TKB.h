#ifndef TKB_H
#define TKB_H

#include <string>
#include <vector>

class SubjectTable {
public:
    std::string IDClass;
    std::string CourseID;
    std::string Course; // Tên học phần
    std::string Name;   // Tên lớp/Môn học
    std::string DayOfWeek;
    std::string Time;
    std::string Place;
    std::string TeacherName;
    
    SubjectTable();
    SubjectTable(std::string _IDClass, std::string _CourseID, std::string _Name, std::string _DayOfWeek, std::string _Time, std::string _Place, std::string _TeacherName);

    static std::vector<SubjectTable> readData(const std::string& filename);
};


#endif
