#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <windows.h>
#include <iostream>
#include <string>

// Màu sắc cho console
namespace Color {
    enum Code {
        BLACK = 0,
        DARK_BLUE = 1,
        DARK_GREEN = 2,
        DARK_CYAN = 3,
        DARK_RED = 4,
        DARK_MAGENTA = 5,
        DARK_YELLOW = 6,
        GRAY = 7,
        DARK_GRAY = 8,
        BLUE = 9,
        GREEN = 10,
        CYAN = 11,
        RED = 12,
        MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };
}

class ConsoleUI {
private:
    HANDLE hConsole;

public:
    ConsoleUI() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    // Đặt màu chữ
    void setColor(int textColor, int bgColor = 0) {
        SetConsoleTextAttribute(hConsole, textColor + (bgColor * 16));
    }

    // Reset màu về mặc định
    void resetColor() {
        setColor(Color::WHITE, Color::BLACK);
    }

    // Xóa màn hình
    void clearScreen() {
        system("cls");
    }

    // In tiêu đề
    void printTitle(const std::string& title) {
        clearScreen();
        setColor(Color::CYAN, Color::BLACK);
        std::cout << "\n";
        std::cout << "╔════════════════════════════════════════════════════════════════════════════╗\n";
        setColor(Color::YELLOW, Color::BLACK);
        std::cout << "║" << std::string(30, ' ') << title << std::string(30, ' ') << "║\n";
        setColor(Color::CYAN, Color::BLACK);
        std::cout << "╚════════════════════════════════════════════════════════════════════════════╝\n";
        resetColor();
    }

    // In menu
    void printMenu() {
        setColor(Color::GREEN, Color::BLACK);
        std::cout << "\n╔════════════════════════ MENU CHUC NANG ════════════════════════╗\n";
        resetColor();
        std::cout << "║  ";
        setColor(Color::YELLOW);
        std::cout << "1";
        resetColor();
        std::cout << ". Xem toan bo thoi khoa bieu                                  ║\n";
        
        std::cout << "║  ";
        setColor(Color::YELLOW);
        std::cout << "2";
        resetColor();
        std::cout << ". Xem theo ten giao vien                                      ║\n";
        
        std::cout << "║  ";
        setColor(Color::YELLOW);
        std::cout << "3";
        resetColor();
        std::cout << ". Xem theo ma hoc phan                                        ║\n";
        
        std::cout << "║  ";
        setColor(Color::YELLOW);
        std::cout << "4";
        resetColor();
        std::cout << ". Xem theo ngay trong tuan                                    ║\n";
        
        std::cout << "║  ";
        setColor(Color::YELLOW);
        std::cout << "5";
        resetColor();
        std::cout << ". Chinh sua TKB                                                ║\n";
        
        setColor(Color::GREEN);
        std::cout << "╚═════════════════════════════════════════════════════════════════╝\n";
        resetColor();
        
        setColor(Color::CYAN);
        std::cout << "Chon lua chon (1-5): ";
        resetColor();
    }

    // In thông báo thành công
    void printSuccess(const std::string& message) {
        setColor(Color::GREEN);
        std::cout << "✓ " << message << std::endl;
        resetColor();
    }

    // In thông báo lỗi
    void printError(const std::string& message) {
        setColor(Color::RED);
        std::cout << "✗ " << message << std::endl;
        resetColor();
    }

    // In thông báo cảnh báo
    void printWarning(const std::string& message) {
        setColor(Color::YELLOW);
        std::cout << "⚠ " << message << std::endl;
        resetColor();
    }

    // In thông tin
    void printInfo(const std::string& message) {
        setColor(Color::CYAN);
        std::cout << "ℹ " << message << std::endl;
        resetColor();
    }

    // In đường kẻ
    void printLine(char c = '=', int length = 80) {
        setColor(Color::DARK_GRAY);
        std::cout << std::string(length, c) << std::endl;
        resetColor();
    }

    // Đợi người dùng nhấn phím
    void waitForKey() {
        setColor(Color::DARK_GRAY);
        std::cout << "\nNhan phim bat ky de tiep tuc...";
        resetColor();
        std::cin.get();
    }
};

#endif
