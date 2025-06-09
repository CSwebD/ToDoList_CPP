#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>  // For system() function

class Task {
public:
    std::string description;
    bool isCompleted;
    std::string dateAdded;
    std::string dateCompleted;

    Task(const std::string& desc) : description(desc), isCompleted(false) {
        time_t now = time(0);
        char timeStr[26];
        ctime_s(timeStr, sizeof(timeStr), &now);
        dateAdded = timeStr;
        dateAdded.pop_back(); // Remove newline
    }

    void markCompleted() {
        isCompleted = true;
        time_t now = time(0);
        char timeStr[26];
        ctime_s(timeStr, sizeof(timeStr), &now);
        dateCompleted = timeStr;
        dateCompleted.pop_back(); // Remove newline
    }
};

class ToDoApp {
private:
    std::vector<Task> tasks;
    std::vector<Task> completedTasks;
    int currentTaskIndex;

public:
    ToDoApp() : currentTaskIndex(0) {}

    // Window A: Add tasks
    void addTasksWindow() {
        std::cout << "\n=== ToDoList Application ===" << std::endl;
        std::cout << "=== Add Tasks Window ===" << std::endl;

        std::string task;
        char choice;

        do {
            std::cout << "\nEnter a task: ";
            std::cin.ignore();
            std::getline(std::cin, task);

            if (!task.empty()) {
                tasks.push_back(Task(task));
                std::cout << "Task added successfully!" << std::endl;
            }

            std::cout << "Add another task? (y/n): ";
            std::cin >> choice;

        } while (choice == 'y' || choice == 'Y');

        if (!tasks.empty()) {
            std::cout << "\nTotal tasks added: " << tasks.size() << std::endl;
            std::cout << "Press any key to continue to task management..." << std::endl;
            std::cin.ignore();
            std::cin.get();
        }
    }

    // Window B: Task management with lifecycle
    void taskManagementWindow() {
        if (tasks.empty()) {
            std::cout << "No tasks available. Please add tasks first." << std::endl;
            return;
        }

        char choice;
        bool continueLoop = true;

        while (continueLoop && !tasks.empty()) {
            system("cls"); // Clear screen for Windows

            std::cout << "\n=== Task Management Window ===" << std::endl;
            std::cout << "Current Task: " << (currentTaskIndex + 1) << " of " << tasks.size() << std::endl;
            std::cout << "Task: " << tasks[currentTaskIndex].description << std::endl;
            std::cout << "Added on: " << tasks[currentTaskIndex].dateAdded << std::endl;

            std::cout << "\nOptions:" << std::endl;
            std::cout << "1. Done - Mark task as completed" << std::endl;
            std::cout << "2. Skip - Move to next task" << std::endl;
            std::cout << "3. Save - Save all progress" << std::endl;
            std::cout << "4. Close - Exit application" << std::endl;
            std::cout << "Choice: ";

            std::cin >> choice;

            switch (choice) {
            case '1': // Done
                markTaskDone();
                break;
            case '2': // Skip
                skipTask();
                break;
            case '3': // Save
                saveProgress();
                std::cout << "Progress saved successfully!" << std::endl;
                std::cout << "Press any key to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            case '4': // Close
                saveProgress();
                std::cout << "Progress saved. Goodbye!" << std::endl;
                continueLoop = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                std::cout << "Press any key to continue...";
                std::cin.ignore();
                std::cin.get();
            }
        }
    }

    void markTaskDone() {
        tasks[currentTaskIndex].markCompleted();
        completedTasks.push_back(tasks[currentTaskIndex]);

        // Save achievement immediately
        saveAchievement(tasks[currentTaskIndex]);

        // Remove completed task from active tasks
        tasks.erase(tasks.begin() + currentTaskIndex);

        std::cout << "Task marked as done and saved to achievements!" << std::endl;

        // Adjust current index if needed
        if (currentTaskIndex >= tasks.size() && !tasks.empty()) {
            currentTaskIndex = 0; // Loop back to beginning
        }

        if (tasks.empty()) {
            std::cout << "Congratulations! All tasks completed!" << std::endl;
            std::cout << "Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
        }
        else {
            std::cout << "Moving to next task..." << std::endl;
            std::cout << "Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }

    void skipTask() {
        currentTaskIndex++;
        if (currentTaskIndex >= tasks.size()) {
            currentTaskIndex = 0; // Loop back to beginning (lifecycle)
        }
        std::cout << "Task skipped. Moving to next task..." << std::endl;
        std::cout << "Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    void saveAchievement(const Task& task) {
        std::ofstream file("achievements.txt", std::ios::app);
        if (file.is_open()) {
            file << "COMPLETED TASK: " << task.description << std::endl;
            file << "Added on: " << task.dateAdded << std::endl;
            file << "Completed on: " << task.dateCompleted << std::endl;
            file << "---" << std::endl;
            file.close();
        }
        else {
            std::cout << "Warning: Could not save achievement to file." << std::endl;
        }
    }

    void saveProgress() {
        // Save current tasks to file
        std::ofstream tasksFile("current_tasks.txt");
        if (tasksFile.is_open()) {
            tasksFile << "=== CURRENT TASKS ===" << std::endl;
            for (size_t i = 0; i < tasks.size(); i++) {
                tasksFile << (i + 1) << ". " << tasks[i].description << std::endl;
                tasksFile << "   Added on: " << tasks[i].dateAdded << std::endl;
                if (i == currentTaskIndex) {
                    tasksFile << "   [CURRENT TASK]" << std::endl;
                }
                tasksFile << std::endl;
            }
            tasksFile.close();
        }

        // Update statistics
        saveStatistics();
    }

    void saveStatistics() {
        std::ofstream statsFile("statistics.txt");
        if (statsFile.is_open()) {
            statsFile << "=== TODOLIST STATISTICS ===" << std::endl;
            statsFile << "Total completed tasks: " << completedTasks.size() << std::endl;
            statsFile << "Remaining tasks: " << tasks.size() << std::endl;
            statsFile << "Total tasks created: " << (completedTasks.size() + tasks.size()) << std::endl;

            if (!completedTasks.empty()) {
                statsFile << "\n=== COMPLETED TASKS SUMMARY ===" << std::endl;
                for (const auto& task : completedTasks) {
                    statsFile << "- " << task.description << " (Completed: " << task.dateCompleted << ")" << std::endl;
                }
            }

            time_t now = time(0);
            char timeStr[26];
            ctime_s(timeStr, sizeof(timeStr), &now);
            statsFile << "\nLast updated: " << timeStr;
            statsFile.close();
        }
    }

    void displayMenu() {
        std::cout << "\n=== ToDoList Application ===" << std::endl;
        std::cout << "1. Add Tasks" << std::endl;
        std::cout << "2. Manage Tasks" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Choice: ";
    }

    void run() {
        int choice;
        bool running = true;

        while (running) {
            displayMenu();
            std::cin >> choice;

            switch (choice) {
            case 1:
                addTasksWindow();
                break;
            case 2:
                if (tasks.empty()) {
                    std::cout << "No tasks available. Please add tasks first." << std::endl;
                    std::cout << "Press any key to continue...";
                    std::cin.ignore();
                    std::cin.get();
                }
                else {
                    taskManagementWindow();
                }
                break;
            case 3:
                saveProgress();
                std::cout << "Thanks for using ToDoList! Goodbye!" << std::endl;
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                std::cout << "Press any key to continue...";
                std::cin.ignore();
                std::cin.get();
            }
        }
    }
};

int main() {
    ToDoApp app;
    app.run();
    return 0;
}