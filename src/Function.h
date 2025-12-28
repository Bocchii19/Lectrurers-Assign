#include <iostream>
#include "TKB.h"
#include "GV.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <algorithm> // for std::find

#ifndef FUNCTION_H
#define FUNCTION_H

// Hàm kiểm tra xung đột thời gian được viết lại an toàn hơn
bool isTimeConflict(const std::string& day1, const std::string& time1, const std::string& day2, const std::string& time2) {
    if (day1 != day2) {
        return false; // Khác ngày thì không trùng
    }

    // Kiểm tra độ dài an toàn
    if (time1.size() < 9 || time2.size() < 9) {
        return false; 
    }

    try {
        // Parse thời gian start-end (Format: HHMM-HHMM)
        int start1 = std::stoi(time1.substr(0, 2)) * 60 + std::stoi(time1.substr(2, 2));
        int end1 = std::stoi(time1.substr(5, 2)) * 60 + std::stoi(time1.substr(7, 2));
        
        int start2 = std::stoi(time2.substr(0, 2)) * 60 + std::stoi(time2.substr(2, 2));
        int end2 = std::stoi(time2.substr(5, 2)) * 60 + std::stoi(time2.substr(7, 2));

        // Nếu khoảng thời gian giao nhau => Xung đột
        // !(end1 <= start2 || end2 <= start1)
        if (start1 < end2 && end1 > start2) {
            return true; 
        }
    } catch (...) {
        // Bắt lỗi nếu chuỗi thời gian không phải số
        return false;
    }

    return false; 
}


// --- THUẬT TOÁN MỚI: CÂN BẰNG TẢI (LOAD BALANCING) ---
// Thay vì assignTeacherToSubject kiểu cũ (chọn người đầu tiên), ta sẽ tìm người tốt nhất
// Người tốt nhất là:
// 1. Có chuyên môn (Subjects chứa subject.Name)
// 2. Không bị trùng lịch
// 3. Đang dạy ÍT LỚP NHẤT (assignedCount nhỏ nhất)

bool assignBestTeacher(SubjectTable& subject, std::vector<Teacher>& listTeacher, std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& teacherSchedule) {
    Teacher* bestCandidate = nullptr;
    int minAssigned = 9999;

    for (auto& teacher : listTeacher) {
        // 1. Kiểm tra chuyên môn (Duyệt qua danh sách môn giáo viên có thể dạy)
        bool canTeach = false;
        for (const auto& role : teacher.Subjects) {
            // So sánh gần đúng hoặc chính xác. Ở đây ta so sánh chính xác tên môn
            if (role == subject.Name) {
                canTeach = true;
                break;
            }
        }
        if (!canTeach) continue;

        // 2. Kiểm tra lịch (Time Conflict)
        bool conflict = false;
        if (teacherSchedule.find(teacher.Name) != teacherSchedule.end()) {
            for (const auto& schedule : teacherSchedule[teacher.Name]) {
                if (isTimeConflict(schedule.first, schedule.second, subject.DayOfWeek, subject.Time)) {
                    conflict = true;
                    break;
                }
            }
        }
        if (conflict) continue;

        // 3. So sánh workload (Load Balancing)
        // Nếu giáo viên này ứng cử được và có ít việc hơn ứng cử viên hiện tại -> chọn
        if (teacher.assignedCount < minAssigned) {
            minAssigned = teacher.assignedCount;
            bestCandidate = &teacher; 
        }
    }

    // Sau khi duyệt hết danh sách, nếu tìm được người phù hợp nhất
    if (bestCandidate != nullptr) {
        subject.TeacherName = bestCandidate->Name;
        
        // Cập nhật lịch bận
        teacherSchedule[bestCandidate->Name].emplace_back(subject.DayOfWeek, subject.Time);
        
        // Tăng biến đếm số lớp đã dạy
        bestCandidate->assignedCount++; 
        
        return true; // Thành công
    }

    return false; // Không tìm được ai
}

void writeScheduleToFile(const std::vector<SubjectTable>& listSubject) {
    std::ofstream file("phancong.csv");
    if (!file.is_open()) {
        std::cerr << "Khong the mo tep de ghi." << std::endl;
        return;
    }

    // Ghi tiêu đề (Header) cho file CSV để dễ đọc hơn
    file << "Ma Lop,Ma HP,Ten Mon,Thu,Gio,Phong,Giang Vien\n";

    for (const auto& subject : listSubject) {
        file << subject.IDClass << ","
             << subject.CourseID << ","
             << subject.Name << ","
             << subject.DayOfWeek << ","
             << subject.Time << ","
             << subject.Place << ","
             << subject.TeacherName << "\n";
    }

    file.close();
}

std::vector<std::vector<std::string>> readFile(const std::string& file_name) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(file_name);
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> row;
        while (getline(ss, item, ',')) {
            row.push_back(item);
        }
        data.push_back(row);
    }
    file.close();
    return data;
}

void writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            if (i != 0) file << ",";
            file << row[i];
        }
        file << std::endl;
    }
    file.close();
}

void editFile(const std::string& file_name, int row, int col, const std::string& newValue) {
    std::vector<std::vector<std::string>> data = readFile(file_name);
    
    if (data.empty()) {
        std::cerr << "Loi: File khong ton tai hoac trong!" << std::endl;
        return;
    }
    
    // Điều chỉnh row vì có thể data đọc cả header hoặc không, tùy cách xử lý
    // Ở đây giả sử row là index từ 0
    if (row < 0 || row >= data.size()) {
        std::cerr << "Loi: Chi so dong khong hop le!" << std::endl;
        return;
    }
    
    if (col < 0 || col >= data[row].size()) {
        std::cerr << "Loi: Chi so cot khong hop le!" << std::endl;
        return;
    }

    data[row][col] = newValue;
    writeCSV(file_name, data);
}

void printMatchingRows(const std::vector<std::vector<std::string>>& data, int col, std::string value) {
    bool found = false;
    for (const auto& row : data) {
        // Tìm kiếm chuỗi con (substring) để linh hoạt hơn
        if (col < row.size() && row[col].find(value) != std::string::npos) {
            for (size_t i = 0; i < row.size(); ++i) {
                std::cout << row[i];
                if (i < row.size() - 1) std::cout << " | ";
            }
            std::cout << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Khong tim thay du lieu phu hop!" << std::endl;
    }
}

void printFile(const std::string& file_name) {
    auto data = readFile(file_name);
    if (data.empty()) {
        std::cout << "File trong hoac khong ton tai!" << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(100, '=') << std::endl;
    std::cout << std::setw(10) << "Ma Lop" << " | "
              << std::setw(10) << "Ma HP" << " | "
              << std::setw(30) << "Ten Mon" << " | " // Tăng độ rộng tên môn
              << std::setw(5) << "Thu" << " | "
              << std::setw(13) << "Gio" << " | "
              << std::setw(8) << "Phong" << " | "
              << "Giang Vien" << std::endl;
    std::cout << std::string(100, '=') << std::endl;
    
    bool isHeader = true; // Cờ để bỏ qua dòng đầu nếu file có header
    for (const auto& row : data) {
        // Simple heuristic: Nếu dòng chứa "Ma Lop" thì là header, skip
        if (row.size() > 0 && row[0] == "Ma Lop") continue;

        if (row.size() >= 7) {
            std::cout << std::setw(10) << row[0] << " | "
                      << std::setw(10) << row[1] << " | "
                      << std::setw(30) << (row[2].size() > 28 ? row[2].substr(0,25)+"..." : row[2]) << " | "
                      << std::setw(5) << row[3] << " | "
                      << std::setw(13) << row[4] << " | "
                      << std::setw(8) << row[5] << " | "
                      << row[6] << std::endl;
        }
    }
    std::cout << std::string(100, '=') << std::endl;
}

#endif
