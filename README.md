# Lecturers Assign System

A C++ Console Application designed to automate the assignment of teachers to courses, featuring a **Load Balancing Algorithm** to ensure fair workload distribution.

## 🚀 Key Features

*   **Automated Assignment**: Automatically assigns the most suitable teacher for each subject based on expertise and availability.
*   **⚖️ Load Balancing**: The system prioritizes teachers with the fewest current assignments to prevent burnout and ensure even distribution.
*   **Time Conflict Detection**: Intelligent checking to prevent scheduling double bookings for teachers.
*   **🖥️ Beautiful Console UI**: A clean, colorful, and user-friendly interface using `ConsoleUI`.
*   **Data Management**:
    *   Reads schedule from `TKB.csv`.
    *   Reads teacher data from `GV.csv`.
    *   Exports results to `phancong.csv`.

## 📂 Project Structure

The project has been refactored to follow standard C++ conventions:

```
Lecturers-Assign/
├── include/           # Header files (.h) containing declarations
│   ├── GV.h           # Teacher class
│   ├── TKB.h          # Subject/Schedule class
│   ├── Function.h     # Core logic & algorithms
│   └── ConsoleUI.h    # UI components
├── src/               # Source files (.cpp) containing implementations
│   ├── GV.cpp
│   ├── TKB.cpp
│   ├── Function.cpp
│   └── ConsoleUI.cpp
├── main.cpp           # Application entry point
├── TKB.csv            # Input: Schedule data
├── GV.csv             # Input: Teacher data
└── README.md
```

## 🛠️ Installation & Usage

### Prerequisites
*   A C++ Compiler (GCC/G++ recommended)
*   Git

### Compilation
Open your terminal/command prompt in the project directory and run:

```bash
g++ -std=c++11 -I include main.cpp src/*.cpp -o main.exe
```

### Running the Application
After successful compilation:

```bash
./main.exe
```

## 📝 How It Works

1.  **Read Data**: The system loads course details and teacher profiles from CSV files.
2.  **Processing**: It iterates through each course and finds valid teacher candidates.
3.  **Selection**: Among valid candidates (right subject, no time conflict), the algorithm selects the teacher with the **lowest current workload**.
4.  **Output**: The final assignment schedule is displayed on screen and saved to `phancong.csv`.

## 👤 Author

*   **Bocchii19**
