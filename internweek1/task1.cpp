#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Structure to store student details
struct Student {
    int rollNo;
    string name;
    int marks[5];
    int total;
    float average;
    char grade;
};

const int MAX_STUDENTS = 100;
Student students[MAX_STUDENTS];
int studentCount = 0;
const string FILENAME = "students.txt";

// Function prototypes
void addStudent();
void viewAllStudents();
void searchByRollNo();
void saveToFile();
void loadFromFile();
char calculateGrade(float average);

int main() {
    loadFromFile();
    
    int choice;
    
    do {
        cout << "\n=== STUDENT RESULT MANAGEMENT SYSTEM ===" << endl;
        cout << "1. Add New Student" << endl;
        cout << "2. View All Students" << endl;
        cout << "3. Search by Roll No" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                searchByRollNo();
                break;
            case 4:
                saveToFile();
                cout << "Data saved successfully. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while(choice != 4);
    
    return 0;
}

// Function to add a new student
void addStudent() {
    if(studentCount >= MAX_STUDENTS) {
        cout << "Maximum number of students reached!" << endl;
        return;
    }
    
    Student s;
    cout << "\nEnter Student Details:" << endl;
    cout << "Roll No: ";
    cin >> s.rollNo;
    cin.ignore(); // Clear input buffer
    cout << "Name: ";
    getline(cin, s.name);
    
    s.total = 0;
    cout << "Enter marks for 5 subjects:" << endl;
    for(int i = 0; i < 5; i++) {
        cout << "Subject " << (i+1) << ": ";
        cin >> s.marks[i];
        s.total += s.marks[i];
    }
    
    s.average = s.total / 5.0;
    s.grade = calculateGrade(s.average);
    
    students[studentCount++] = s;
    cout << "Student added successfully!" << endl;
}

// Function to view all students
void viewAllStudents() {
    if(studentCount == 0) {
        cout << "No students found!" << endl;
        return;
    }
    
    cout << "\n" << setw(70) << setfill('=') << "" << endl;
    cout << setfill(' ') << setw(5) << "Roll" << setw(20) << "Name" 
         << setw(25) << "Total Marks" << setw(10) << "Average" 
         << setw(8) << "Grade" << endl;
    cout << setw(70) << setfill('=') << "" << endl;
    cout << setfill(' ');
    
    for(int i = 0; i < studentCount; i++) {
        cout << setw(5) << students[i].rollNo 
             << setw(20) << students[i].name 
             << setw(25) << students[i].total 
             << setw(10) << fixed << setprecision(2) << students[i].average
             << setw(8) << students[i].grade << endl;
    }
}

// Function to search student by roll number
void searchByRollNo() {
    if(studentCount == 0) {
        cout << "No students found!" << endl;
        return;
    }
    
    int rollNo;
    cout << "Enter Roll No to search: ";
    cin >> rollNo;
    
    bool found = false;
    for(int i = 0; i < studentCount; i++) {
        if(students[i].rollNo == rollNo) {
            cout << "\nStudent Found:" << endl;
            cout << "Roll No: " << students[i].rollNo << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Marks: ";
            for(int j = 0; j < 5; j++) {
                cout << students[i].marks[j] << " ";
            }
            cout << "\nTotal: " << students[i].total << endl;
            cout << "Average: " << students[i].average << endl;
            cout << "Grade: " << students[i].grade << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "Student with Roll No " << rollNo << " not found!" << endl;
    }
}

// Function to calculate grade based on average
char calculateGrade(float average) {
    if(average >= 90) return 'A';
    else if(average >= 80) return 'B';
    else if(average >= 70) return 'C';
    else if(average >= 60) return 'D';
    else return 'F';
}

// Function to save data to file
void saveToFile() {
    ofstream outFile(FILENAME);
    if(!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    for(int i = 0; i < studentCount; i++) {
        outFile << students[i].rollNo << endl;
        outFile << students[i].name << endl;
        for(int j = 0; j < 5; j++) {
            outFile << students[i].marks[j] << " ";
        }
        outFile << endl;
    }
    
    outFile.close();
}

// Function to load data from file
void loadFromFile() {
    ifstream inFile(FILENAME);
    if(!inFile) {
        cout << "No existing data file found. Starting fresh." << endl;
        return;
    }
    
    studentCount = 0;
    while(inFile && studentCount < MAX_STUDENTS) {
        Student s;
        inFile >> s.rollNo;
        inFile.ignore();
        getline(inFile, s.name);
        
        s.total = 0;
        for(int i = 0; i < 5; i++) {
            inFile >> s.marks[i];
            s.total += s.marks[i];
        }
        
        s.average = s.total / 5.0;
        s.grade = calculateGrade(s.average);
        
        students[studentCount++] = s;
    }
    
    inFile.close();
    cout << "Data loaded successfully!" << endl;
}