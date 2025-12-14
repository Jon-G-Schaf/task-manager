# Simple Task Manager

A minimal C++ GUI application using Qt that meets the project requirements.

## Requirements Met

### 3 GUI Pages
1. **Task List Page** - View all tasks, mark them complete
2. **Add Task Page** - Enter and add new tasks  
3. **Statistics Page** - View completion stats

### 3 Different Functions
1. **addTask()** - Creates a new task and adds it to the list
2. **markComplete()** - Marks the selected task as completed
3. **updateStats()** - Calculates and displays task statistics

## Quick Setup

### Windows (Recommended: Qt installer)
```bash
# Install Qt from https://www.qt.io/download-qt-installer
# Then in project folder:
mkdir build && cd build
cmake ..
cmake --build .
./taskmanager
```

### Ubuntu/Debian
```bash
sudo apt install qt6-base-dev cmake build-essential
# OR for Qt5: sudo apt install qt5-default cmake build-essential

mkdir build && cd build
cmake ..
make
./taskmanager
```

### macOS
```bash
brew install qt cmake
mkdir build && cd build
cmake ..
make
./taskmanager
```

## Project Structure
```
task-manager/
├── main.cpp        # All application code (single file for simplicity)
├── CMakeLists.txt  # Build configuration
└── README.md       # This file
```

## How It Works

The app uses a `QStackedWidget` to switch between 3 pages. Tasks are stored in a simple `std::vector<Task>` with fake initial data. The UI is minimal but functional.

**Key interaction**: Add tasks → View them in list → Mark complete → Check stats
