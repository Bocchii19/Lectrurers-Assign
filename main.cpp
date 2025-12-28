#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

#include "TKB.h"
#include "GV.h"
#include "Function.h"
#include "ConsoleUI.h" 

using namespace std; // Trong file .cpp chính thì có thể dùng (nhưng trong .h thì nên tránh)

int main() {
    ConsoleUI ui; // Khởi tạo đối tượng UI
    ui.printTitle("HE THONG PHAN CONG GIANG VIEN (CAN BANG TAI)");

    // 1. Đọc dữ liệu từ file CSV
    vector<SubjectTable> listSubject = SubjectTable::readData("TKB.csv");
    vector<Teacher> listTeacher = Teacher::readData("GV.csv");
    
    // Map lưu lịch dạy: Tên GV -> List<Thứ, Giờ>
    unordered_map<string, vector<pair<string, string>>> teacherSchedule; 

    // 2. Phân công giảng viên (Sử dụng thuật toán Cân Bằng Tải mới)
    cout << "\nDang phan cong tu dong..." << endl;
    
    int unassignedCount = 0;
    for (auto& subject : listSubject) {
        // Gọi hàm mới: assignBestTeacher thay vì assignTeacherToSubject
        // Hàm này sẽ tự động chọn GV phù hợp nhất (rảnh nhất)
        bool assigned = assignBestTeacher(subject, listTeacher, teacherSchedule);
        
        if (!assigned) {
            unassignedCount++;
            // Bỏ qua hiển thị cảnh báo quá nhiều nếu muốn clean terminal
            // nhưng giữ lại để user biết
            // cout << " [!] Khong tim duoc GV cho lop: " << subject.IDClass << " - " << subject.Name << endl; 
        }
    }
    
    // 3. Ghi kết quả
    writeScheduleToFile(listSubject);
    
    // 4. Hiển thị báo cáo thống kê
    cout << endl;
    ui.printSuccess("=== PHAN CONG HOAN TAT ===");
    cout << "  > Tong so lop: " << listSubject.size() << endl;
    cout << "  > Da phan cong: " << (listSubject.size() - unassignedCount) << endl;
    cout << "  > Chua phan cong: ";
    if (unassignedCount > 0) ui.printError(to_string(unassignedCount) + " (Can kiem tra lai)");
    else ui.printSuccess("0 (Hoan hao!)");
    
    cout << "\nKet qua da duoc luu vao file 'phancong.csv'\n" << endl;
    
    // 5. Menu chức năng
    char x;
    do {
        // Load lại data từ file vừa ghi để đảm bảo tính nhất quán khi edit
        auto data = readFile("phancong.csv");
        
        ui.printTitle("MENU CHUC NANG");
        cout << "1. Xem toan bo thoi khoa bieu" << endl;
        cout << "2. Xem theo ten giao vien" << endl;
        cout << "3. Xem theo ma hoc phan" << endl;
        cout << "4. Xem theo ngay trong tuan" << endl;
        cout << "5. Chinh sua TKB (Sua truc tiep)" << endl;
        cout << "6. Thong ke tai nang (Top GV day nhieu)" << endl;
        cout << "------------------------------------" << endl;
        cout << "Chon chuc nang (1-6): ";
        
        string value;
        int option;
        
        if (!(cin >> option)) {
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            ui.printError("Loi: Vui long nhap so!");
            continue;
        }
        
        if(option == 1) { // IN TOÀN BỘ
            printFile("phancong.csv");
        } 
        else if (option == 2) { // TÌM THEO GV
            // Hiển thị danh sách GV để user dễ chọn
            cout << "Danh sach GV: ";
            for(int i=0; i < min((int)listTeacher.size(), 5); ++i) cout << listTeacher[i].Name << ", ";
            cout << "..." << endl;

            cout << "Nhap ten giang vien (co the nhap ten gan dung): ";
            cin.ignore();
            getline(cin, value);
            printMatchingRows(data, 6, value);
        } 
        else if (option == 3) { // TÌM THEO MÃ HP
            cout << "Nhap ma hoc phan: ";
            cin.ignore();
            getline(cin, value);
            printMatchingRows(data, 1, value);
        } 
        else if (option == 4) { // TÌM THEO NGÀY
            cout << "\n--- CHON NGAY ---" << endl;
            vector<string> days = {"", "Thu 2", "Thu 3", "Thu 4", "Thu 5", "Thu 6", "Thu 7", "Chu nhat"};
            for(int i = 1; i <= 7; ++i){
                cout << "\n>> " << days[i] << " <<" << endl;
                printMatchingRows(data, 3, to_string(i));
            }        
        } 
        else if (option == 5) { // CHỈNH SỬA
            ui.printTitle("CHINH SUA DU LIEU");
            cout << "1. Sua ten giang vien" << endl;
            cout << "2. Sua thoi gian" << endl;
            cout << "3. Sua phong hoc" << endl;
            cout << "Chon loai chinh sua: ";
            
            int option_t;
            cin >> option_t;
            
            cout << "Nhap so dong (STT) muon sua (xem o Cot dau tien neu co, hoac dem tu 1): ";
            int row;
            cin >> row;
            
            cin.ignore();
            cout << "Nhap gia tri moi: ";
            getline(cin, value);
            
            // Map option sang index cột trong CSV (0-based)
            // Cột: 0-ID, 1-CourseID, 2-Name, 3-Day, 4-Time, 5-Place, 6-Teacher
            int colIndex = -1;
            if(option_t == 1) colIndex = 6;
            else if(option_t == 2) colIndex = 4;
            else if(option_t == 3) colIndex = 5;
            
            if(colIndex != -1) {
                // row - 1 vì mảng bắt đầu từ 0
                // Tuy nhiên hàm editFile cần check lại logic index
                editFile("phancong.csv", row, colIndex, value); 
                ui.printSuccess("Cap nhat thanh cong!");
            } else {
                ui.printError("Lua chon khong hop le!");
            }
        }
        else if (option == 6) { // THỐNG KÊ (Mới)
            ui.printTitle("THONG KE TAI NANG");
            // Sắp xếp GV theo số lớp giảm dần
            sort(listTeacher.begin(), listTeacher.end(), [](const Teacher& a, const Teacher& b){
                return a.assignedCount > b.assignedCount;
            });
            
            cout << setw(30) << left << "Ten Giang Vien" << " | " << "So lop day" << endl;
            cout << string(45, '-') << endl;
            for(const auto& gv : listTeacher) {
                if(gv.assignedCount > 0)
                    cout << setw(30) << left << gv.Name << " | " << gv.assignedCount << endl;
            }
        }
        else {
            ui.printError("Lua chon khong hop le!");
        }
        
        cout << "\nTiep tuc chuong trinh? (y/n): ";
        cin >> x;
        cin.ignore(); 
    } while (x == 'y' || x == 'Y');
    
    return 0;
}
