#include "ConsoleUI.h"
#include <iostream>

ConsoleUI::ConsoleUI() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsoleUI::setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(hConsole, textColor + (bgColor * 16));
}

void ConsoleUI::resetColor() {
    setColor(Color::WHITE, Color::BLACK);
}

void ConsoleUI::clearScreen() {
    system("cls");
}

void ConsoleUI::printTitle(const std::string& title) {
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

void ConsoleUI::printMenu() {
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

void ConsoleUI::printSuccess(const std::string& message) {
    setColor(Color::GREEN);
    std::cout << "✓ " << message << std::endl;
    resetColor();
}

void ConsoleUI::printError(const std::string& message) {
    setColor(Color::RED);
    std::cout << "✗ " << message << std::endl;
    resetColor();
}

void ConsoleUI::printWarning(const std::string& message) {
    setColor(Color::YELLOW);
    std::cout << "⚠ " << message << std::endl;
    resetColor();
}

void ConsoleUI::printInfo(const std::string& message) {
    setColor(Color::CYAN);
    std::cout << "ℹ " << message << std::endl;
    resetColor();
}

void ConsoleUI::printLine(char c, int length) {
    setColor(Color::DARK_GRAY);
    std::cout << std::string(length, c) << std::endl;
    resetColor();
}

void ConsoleUI::waitForKey() {
    setColor(Color::DARK_GRAY);
    std::cout << "\nNhan phim bat ky de tiep tuc...";
    resetColor();
    std::cin.get();
}
