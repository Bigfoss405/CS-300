#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// Structure to hold course information
struct Course {
    string courseId;
    string courseName;
    vector<string> prerequisites;
};

// Function to load course data from a file into the hash table
void loadCourses(const string& fileName, unordered_map<string, Course>& courseTable) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseId, courseName, prerequisite;
        getline(ss, courseId, ',');
        getline(ss, courseName, ',');

        Course course;
        course.courseId = courseId;
        course.courseName = courseName;

        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courseTable[courseId] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

// Function to print all courses in alphanumeric order
void printAllCourses(const unordered_map<string, Course>& courseTable) {
    if (courseTable.empty()) {
        cout << "No courses available." << endl;
        return;
    }

    vector<string> courseIds;
    for (const auto& entry : courseTable) {
        courseIds.push_back(entry.first);
    }

    sort(courseIds.begin(), courseIds.end());

    cout << "Here is a sample schedule:" << endl;
    for (const string& courseId : courseIds) {
        const Course& course = courseTable.at(courseId);
        cout << course.courseId << ", " << course.courseName << endl;
    }
}

// Function to print information about a specific course
void printCourse(const unordered_map<string, Course>& courseTable, const string& courseId) {
    string courseIdUpper = courseId;
    transform(courseIdUpper.begin(), courseIdUpper.end(), courseIdUpper.begin(), ::toupper);

    auto it = courseTable.find(courseIdUpper);
    if (it == courseTable.end()) {
        cout << "Course not found: " << courseId << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.courseId << ", " << course.courseName << endl;
    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: \n";
        for (const string& prereqId : course.prerequisites) {
            auto prereqIt = courseTable.find(prereqId);
            if (prereqIt != courseTable.end()) {
                cout << "- " << prereqIt->second.courseId << ", " << prereqIt->second.courseName << endl;
            }
            else {
                cout << "- " << prereqId << " (Course details not available)" << endl;
            }
        }
    }
    else {
        cout << "Prerequisites: None" << endl;
    }
}

int main() {
    unordered_map<string, Course> courseTable;
    string fileName;
    int option;

    cout << "Welcome to the course planner." << endl;

    do {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> option;

        switch (option) {
        case 1:
            fileName = "C:\\Users\\Foster\\Downloads\\CS 300 ABCU_Advising_Program_Input.csv";
            cout << "Loading courses from file: " << fileName << endl;
            loadCourses(fileName, courseTable);
            break;
        case 2:
            printAllCourses(courseTable);
            break;
        case 3: {
            string courseId;
            cout << "What course do you want to know about? ";
            cin >> courseId;
            printCourse(courseTable, courseId);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner" << endl;
            break;
        default:
            cout << option << " is not a valid option." << endl;
        }
    } while (option != 9);

    return 0;
}

