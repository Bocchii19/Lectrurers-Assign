#ifndef GV_H
#define GV_H

#include <string>
#include <vector>

// Declarations only
class Teacher {
public:
    std::string Name;
    std::string telNum;
    std::vector<std::string> Subjects;
    int assignedCount;

    Teacher();
    Teacher(std::string _Name, std::vector<std::string> _Subjects, std::string _telNum);

    static std::vector<Teacher> readData(const std::string& filename);
};

#endif
