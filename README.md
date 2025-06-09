# 📝 ToDoList Application

A feature-rich C++ console application for task management with achievement tracking and lifecycle management.

![Application Demo](screenshots/demo.png)
*Main application interface*

## 🚀 Features

### Core Functionality
- **Task Creation**: Add multiple tasks with automatic timestamping
- **Task Management**: Interactive task processing with lifecycle approach
- **Achievement System**: Automatic saving of completed tasks with timestamps
- **Statistics Tracking**: Comprehensive statistics and progress monitoring
- **Data Persistence**: All data saved to text files for later analysis

### Task Lifecycle
- ✅ **Done**: Mark task as completed → Saves to achievements → Removes from active list
- ⏭️ **Skip**: Move to next task → Cycles back to beginning when reaching end
- 💾 **Save**: Save current progress to files
- 🚪 **Close**: Save everything and exit application

## 📸 Screenshot

![Main Menu](screenshots/ToDoList_CPP_screenshot.png)
*Application startup screen with options*

## 🛠️ Installation & Setup

### Prerequisites
- **Visual Studio 2022** (recommended) or any C++ compiler
- **Windows 10/11** (tested environment)
- **Git** (for cloning the repository)

### Building the Project

#### Using Visual Studio 2022
1. Clone the repository:
   ```bash
   git clone https://github.com/CSwebD/ToDoListApp.git
   cd ToDoListApp
   ```

2. Open Visual Studio 2022
3. File → Open → Project/Solution
4. Select `ToDoListApp.sln`
5. Build the solution: `Ctrl+Shift+B`
6. Run the application: `Ctrl+F5`

#### Using Command Line (MinGW/GCC)
```bash
# Clone repository
git clone https://github.com/CSwebD/ToDoListApp.git
cd ToDoListApp

# Compile
g++ -o todolist.exe ToDoListApp.cpp

# Run
todolist.exe
```

## 📊 Output Files

The application generates three types of files:

| File | Description | Content |
|------|-------------|---------|
| `achievements.txt` | Completed tasks log | Individual completed tasks with timestamps |
| `statistics.txt` | Overall statistics | Summary of completed vs remaining tasks |
| `current_tasks.txt` | Current session state | Active tasks with current position |

### Sample Output Files

**achievements.txt**
```
COMPLETED TASK: Finish project documentation
Added on: Mon Jun 09 14:30:22 2025
Completed on: Mon Jun 09 15:45:33 2025
---
COMPLETED TASK: Review code changes
Added on: Mon Jun 09 14:31:15 2025  
Completed on: Mon Jun 09 16:20:10 2025
---
```

**statistics.txt**
```
=== TODOLIST STATISTICS ===
Total completed tasks: 2
Remaining tasks: 3
Total tasks created: 5

=== COMPLETED TASKS SUMMARY ===
- Finish project documentation (Completed: Mon Jun 09 15:45:33 2025)
- Review code changes (Completed: Mon Jun 09 16:20:10 2025)

Last updated: Mon Jun 09 16:20:10 2025
```

## 🎯 Usage Guide

### Getting Started
1. **Launch the application**
2. **Choose Option 1**: Add your tasks for the day/session
3. **Choose Option 2**: Start managing your tasks
4. **Work through tasks**: Mark as done or skip as needed
5. **Save progress**: Use Save option to persist your work
6. **View achievements**: Check the generated text files

### Task Management Flow
```
Add Tasks → Manage Tasks → [Done/Skip] → Cycle Through → Save → Close
                ↑                                          ↓
                └── Loop back to beginning ←───────────────┘
```

### Best Practices
- Add all your tasks at the beginning of your session
- Use "Done" for completed tasks to build your achievement history
- Use "Skip" to postpone tasks - they'll cycle back for later
- Save regularly to preserve your progress
- Review achievement files to track your productivity

## 🏗️ Technical Details

### Architecture
- **Object-Oriented Design**: Task and ToDoApp classes
- **Memory Management**: Dynamic vector management for tasks
- **File I/O**: Robust file handling for data persistence
- **Error Handling**: Graceful handling of file operations

### Key Classes
- `Task`: Represents individual tasks with metadata
- `ToDoApp`: Main application logic and user interface

### Compiler Compatibility
- **MSVC** (Visual Studio 2022) - Primary target
- **GCC/MinGW** - Cross-platform support
- **C++17 Standard** - Modern C++ features

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch: `git checkout -b feature/AmazingFeature`
3. Commit your changes: `git commit -m 'Add some AmazingFeature'`
4. Push to the branch: `git push origin feature/AmazingFeature`
5. Open a Pull Request

### Future Enhancements
- [ ] GUI version using Qt or Windows Forms
- [ ] Task priority levels
- [ ] Due date management
- [ ] Task categories/tags
- [ ] Export to different formats (CSV, JSON)
- [ ] Task scheduling and reminders

## 📋 Requirements

### System Requirements
- **OS**: Windows 10/11 (primary), Linux/macOS (with minor modifications)
- **RAM**: Minimal (< 50MB)
- **Storage**: < 1MB for application, variable for data files
- **Compiler**: C++17 compatible

### Dependencies
- Standard C++ Library
- File system access for data persistence

## 🐛 Troubleshooting

### Common Issues

**Build Errors with `ctime()`**
- Solution: Project includes `#define _CRT_SECURE_NO_WARNINGS`

**Console Closes Immediately**
- Solution: Use `Ctrl+F5` instead of `F5` in Visual Studio

**Cannot Find Output Files**
- Location: Check `Debug/` or `Release/` folder in project directory
- Alternative: Look in the same folder as the executable

**Permission Errors**
- Solution: Run as administrator or check folder permissions

## 📞 Support

- **Issues**: Open an issue on GitHub
- **Questions**: Create a discussion in the repository
- **Email**: [Your email if you want to provide it]

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Built with Visual Studio 2022
- Inspired by productivity and time management principles
- Thanks to the C++ community for best practices

---

**⭐ If you find this project helpful, please consider giving it a star!**

---

*Last updated: June 2025*
