#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <sstream>
#include <stdexcept>
using namespace std;

void centerText(const string& text) {
    int consoleWidth = 80;
    int padding = (consoleWidth - text.length()) / 2;
    cout << setw(padding + text.length()) << text << endl;
}

string intToString(int value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

class Person {
protected:
    string name;
    string rollno;

public:
    virtual void inputDetails() {
        system("CLS");
        centerText("****************************");
        centerText("*     QUIZ REGISTRATION    *");
        centerText("****************************");
        cout << "\n";

        cout << setw(40) << "Enter Name: ";
        getline(cin, name);
        cout << setw(40) << "Enter Roll No: ";
        getline(cin, rollno);
    }

    virtual void displayDetails() const {
        cout << setw(40) << "Name: " << name << endl;
        cout << setw(40) << "Roll No: " << rollno << endl;
    }

    string getName() const { return name; }
    string getRollNo() const { return rollno; }
};

class Student : public Person {
private:
    int marks = 0;
    float percentage = 0.0;

public:
    void setMarks(int m) {
        if (m < 0 || m > 10) throw invalid_argument("Marks must be between 0 and 10.");
        marks = m;
    }

    int getMarks() const { return marks; }

    void calculatePercentage() {
        percentage = (static_cast<float>(marks) / 10) * 100;
    }

    void displayResult() {
        calculatePercentage();
        centerText("****************************");
        centerText("*        RESULTS           *");
        centerText("****************************");
        cout << "\n";
        displayDetails();
        cout << setw(40) << "Marks: " << marks << " / 10" << endl;
        cout << setw(40) << "Percentage: " << fixed << setprecision(2) << percentage << " %" << endl;
        cout << setw(40) << "Status: " << (marks >= 5 ? "Pass" : "Fail") << endl;

        if (marks == 10) {
            centerText("****************************");
            centerText("*  YOU'RE A C++ GENIUS!    *");
            centerText("****************************");
        } else if (marks >= 8) {
            centerText("Great job! Keep up the good work!");
        } else if (marks >= 5) {
            centerText("Good effort! You can aim even higher!");
        } else {
            centerText("Don't give up! Keep practicing to improve!");
        }
    }
};

void validateStudent(const Student& student) {
    if (student.getName().empty() || student.getRollNo().empty()) {
        throw invalid_argument("Student details are incomplete!");
    }
}

class Quiz {
private:
    Student student;

public:
    void startQuiz() {
        try {
            student.inputDetails();
            validateStudent(student);
            system("CLS");

            centerText("*****************************************");
            centerText("*        WELCOME TO THE C++ QUIZ        *");
            centerText("*****************************************");
            cout << "\n\n";
            centerText("Starting the quiz in...");
            for (int i = 3; i > 0; i--) {
                centerText(intToString(i) + "...");
                Sleep(1000);
            }
            system("CLS");
            askQuestions();
            system("CLS");
            student.displayResult();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

private:
    void askQuestions() {
        const string questions[10] = {
            "What is the correct syntax to include a header file in C++?\nA) #include <header>\nB) #include 'header'\nC) #include {header}\nD) #include [header]",
            "Which of the following is NOT a C++ access specifier?\nA) public\nB) private\nC) protected\nD) global",
            "What is function overriding in C++?\nA) Defining multiple functions with the same name\nB) Redefining a base class function in a derived class\nC) Allocating memory for a function\nD) Binding data and functions together",
            "What is the purpose of inheritance in C++?\nA) To hide data\nB) To reuse code\nC) To allocate memory\nD) To define macros",
            "What is the default access specifier for class members in C++?\nA) public\nB) private\nC) protected\nD) none of the above",
            "Which of the following is a feature of OOP?\nA) Encapsulation\nB) Polymorphism\nC) Inheritance\nD) All of the above",
            "What is the output of the following code: cout << 5 + 2 * 3;\nA) 11\nB) 16\nC) 21\nD) 8",
            "Which of the following is a valid declaration of a pointer in C++?\nA) int *ptr;\nB) int ptr*;\nC) ptr int*;\nD) int &ptr;",
            "What does the 'new' keyword do in C++?\nA) Allocates memory\nB) Deallocates memory\nC) Creates a new variable\nD) None of the above",
            "Which of the following is used to handle exceptions in C++?\nA) try-catch\nB) if-else\nC) switch-case\nD) for-loop"
        };
        char correctAnswers[10] = {'A', 'D', 'B', 'B', 'B', 'D', 'A', 'A', 'A', 'A'};

        for (int i = 0; i < 10; i++) {
            system("CLS");
            centerText("*****************************************");
            centerText("*        WELCOME TO THE C++ QUIZ        *");
            centerText("*****************************************");
            cout << "\n\n";
            centerText("Progress: " + intToString(i + 1) + " / 10 questions");

            cout << "\n";
            centerText("------------------------------------");
            centerText("Question " + intToString(i + 1) + ": " + questions[i]);
            cout << setw(40) << "Answer: ";
            char choice = toupper(getch());
            cout << choice << "\n";

            // Check if the answer is correct
            if (choice == correctAnswers[i]) {
                centerText("Correct!");
                student.setMarks(student.getMarks() + 1);
            } else {
                centerText("Incorrect! The correct answer is: " + string(1, correctAnswers[i]));
            }

            // If it's not the last question, prompt to continue
            if (i < 9) {
                centerText("Press any key to continue to the next question...");
                getch();
            } else {
                // For the last question, wait for a moment before showing results
                centerText("Press any key to see your results...");
                getch();
            }
        }
    }
};

int main() {
    char press;
    do {
        system("CLS");
        Quiz quiz;
        quiz.startQuiz();
        cout << "\n";
        centerText("Press Y to retry or any other key to exit.");
        press = toupper(getch());
    } while (press == 'Y');
    return 0;
}
