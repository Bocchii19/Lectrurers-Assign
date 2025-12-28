#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#ifndef GV_H
#define GV_H

// Không dùng 'using namespace std;' để tránh xung đột tên (Best Practice)
// Chỉ dùng std:: trước các kiểu dữ liệu chuẩn

class Teacher {
public:
    std::string Name;
    std::string telNum;
    std::vector<std::string> Subjects; // Thay Subject1, Subject2 bằng vector để linh hoạt
    int assignedCount; // Biến đếm số lớp đã được phân công (Dùng cho thuật toán Cân Bằng Tải)

    Teacher() : assignedCount(0) {}
    
    // Constructor cập nhật
    Teacher(std::string _Name, std::vector<std::string> _Subjects, std::string _telNum)
        : Name(_Name), Subjects(_Subjects), telNum(_telNum), assignedCount(0) {}

    static std::vector<Teacher> readData(const std::string& filename) {
        std::vector<Teacher> teachers;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Loi: Khong the mo file " << filename << std::endl;
            return teachers;
        }

        std::string line;
        while (getline(file, line)) {
            if (line.empty()) continue; // Bỏ qua dòng trống

            std::stringstream ss(line);
            std::string Name, telNum, Sub1, Sub2;
            
            // Format CSV cũ: Name, Tel, Sub1, Sub2
            std::getline(ss, Name, ',');
            std::getline(ss, telNum, ',');
            std::getline(ss, Sub1, ',');
            std::getline(ss, Sub2, ',');

            std::vector<std::string> subjectList;
            if (!Sub1.empty()) subjectList.push_back(Sub1);
            if (!Sub2.empty() && Sub2 != "\r") subjectList.push_back(Sub2); // Xử lý ký tự xuống dòng nếu có

            teachers.push_back(Teacher(Name, subjectList, telNum));
        }

        file.close();
        return teachers;
    }
};

#endif
