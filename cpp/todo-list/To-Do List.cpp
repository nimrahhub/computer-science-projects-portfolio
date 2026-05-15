#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// Structure to hold task data and status
struct Task {
    string description;
    bool isCompleted;
};

// Function prototypes for clean structure
void loadTasksFromFile(vector<Task>& tasks);
void saveTasksToFile(const vector<Task>& tasks);
void addTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void markTaskComplete(vector<Task>& tasks);
void deleteTask(vector<Task>& tasks);
void clearInputBuffer();

int main() {
    vector<Task> tasks;
    loadTasksFromFile(tasks); // Load existing tasks at startup
    int choice;

    do {
        cout << "\n===============================\n";
        cout << "       ADVANCED TO-DO LIST     \n";
        cout << "===============================\n";
        cout << "1. ➕ Add Task\n";
        cout << "2. 👁️  View Tasks\n";
        cout << "3. ✅ Mark Task as Complete\n";
        cout << "4. ❌ Delete Task\n";
        cout << "5. 🚪 Save and Exit\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskComplete(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                saveTasksToFile(tasks);
                cout << "Tasks saved successfully. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please pick options 1-5.\n";
        }
    } while (choice != 5);

    return 0;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void loadTasksFromFile(vector<Task>& tasks) {
    ifstream inFile("tasks.txt");
    if (!inFile) return; // No file exists yet

    string statusStr, desc;
    while (getline(inFile, statusStr, '|')) {
        if (getline(inFile, desc)) {
            Task t;
            t.isCompleted = (statusStr == "1");
            t.description = desc;
            tasks.push_back(t);
        }
    }
    inFile.close();
}

void saveTasksToFile(const vector<Task>& tasks) {
    ofstream outFile("tasks.txt");
    for (const auto& t : tasks) {
        outFile << t.isCompleted << "|" << t.description << "\n";
    }
    outFile.close();
}

void addTask(vector<Task>& tasks) {
    clearInputBuffer();
    string desc;
    cout << "Enter the new task: ";
    getline(cin, desc);
    
    if (!desc.empty()) {
        tasks.push_back({desc, false});
        cout << "Task added successfully!\n";
    } else {
        cout << "Task cannot be empty!\n";
    }
}

void viewTasks(const vector<Task>& tasks) {
    cout << "\n--- CURRENT TASKS ---\n";
    if (tasks.empty()) {
        cout << "Your to-do list is empty.\n";
        return;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [";
        cout << (tasks[i].isCompleted ? "✔ Complete" : "  Pending ");
        cout << "] " << tasks[i].description << "\n";
    }
}

void markTaskComplete(vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;

    size_t index;
    cout << "Enter task number to mark complete: ";
    if (cin >> index && index > 0 && index <= tasks.size()) {
        tasks[index - 1].isCompleted = true;
        cout << "Task marked as complete!\n";
    } else {
        cout << "Invalid task number.\n";
        clearInputBuffer();
    }
}

void deleteTask(vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;

    size_t index;
    cout << "Enter task number to delete: ";
    if (cin >> index && index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + (index - 1));
        cout << "Task deleted successfully!\n";
    } else {
        cout << "Invalid task number.\n";
        clearInputBuffer();
    }
}
