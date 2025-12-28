#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <windows.h>
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
    ConsoleUI();

    void setColor(int textColor, int bgColor = 0);
    void resetColor();
    void clearScreen();
    
    void printTitle(const std::string& title);
    void printMenu();
    void printSuccess(const std::string& message);
    void printError(const std::string& message);
    void printWarning(const std::string& message);
    void printInfo(const std::string& message);
    void printLine(char c = '=', int length = 80);
    void waitForKey();
};

#endif
