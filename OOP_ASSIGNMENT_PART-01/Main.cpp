#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;
class Rooms;
class Labs;
class Student {
public:
    string name;
    int id;
    string section;
    int Studentid, phoneNumber;
    vector<string> sections;  // Sections in which the students enroll
    vector<string> studentList; // Vector to store student names
    // Constructor
    Student() { }
    Student(const string& name, int id, string sect) : name(name), id(id), section(sect) {}
    void showListOfStudents() {
        ifstream inputFile("Student.txt");
        if (!inputFile.is_open()) {
            cerr << "Failed to open the file.\n";
            return;
        }
        string studentName;
        while (getline(inputFile, studentName)) {
            cout << studentName << endl;
            studentList.push_back(studentName); // Store each student name in the vector
        }
        inputFile.close();
    }

    void addStudent(const string& newStudent, const string& className, const string& enrollment) {
        // Construct the student information string
        string studentInfo = newStudent + " " + className + " " + enrollment;

        // Add new student to the vector
        studentList.push_back(studentInfo);

        // Open the file in append mode
        ofstream outputFile("Student.txt", ios::app);
        if (!outputFile.is_open()) {
            cerr << "Failed to open the file.\n";
            return;
        }

        // Write the new student's information to the file
        outputFile << studentInfo << endl;

        // Close the file
        outputFile.close();
    }
    void removeStudent(const string& studentToRemove) {
        auto it = studentList.begin();
        while (it != studentList.end()) {
            if (*it == studentToRemove) {
                it = studentList.erase(it); // Remove the student if found
                cout << "Student removed.\n";
                return; // Exit the function after removing the student
            }
            else {
                ++it;
            }
        }
        cout << "Student not found in the list.\n";
    }
};
class Teacher {
public:
    string tName;
    string specialization;
    int teacherid, phoneNumber;
    string address;
    vector<string> sections;  // Sections in which the students enroll
    vector<string> teacherList; // Vector to store student names
    // Constructor
    Teacher() {}
    Teacher(const string& name, string spe) : tName(name), specialization(spe) {}
    void showListOfTeachers() {
        ifstream inputFile("Teacher.txt");
        if (!inputFile.is_open()) {
            cerr << "Failed to open the file.\n";
            return;
        }
        string teacherName;
        while (getline(inputFile, teacherName)) {
            cout << teacherName << endl;
            teacherList.push_back(teacherName); // Store each student name in the vector
        }
        inputFile.close();
    }
};
class Labs {
public:
    string labNumber;
    int capacity;

    Labs(const string& lab, int cap) : labNumber(lab), capacity(cap) {}
};
class Courses {
public:
    string courseName;
    string courseID;
    string classTime;
    Teacher* teachers;
    Rooms* rooms;
    string dayOfWeek;
    string section;
    int courseCode;
    string name;
    vector<string> sections;  // Sections in which the students enroll
    vector<string> courseList; // Vector to store student names
    //constructor
    Courses() { }
    Courses(const string& name, const string& id, const string& time, Teacher* t, Rooms* r, string sect) :courseName(name), courseID(id), classTime(time), teachers(t), rooms(r), section(sect) {}
    void showListOfCourses() {
        ifstream inputFile("Course.txt");
        if (!inputFile.is_open()) {
            cerr << "Failed to open the file.\n";
            return;
        }
        string courseName;
        while (getline(inputFile, courseName)) {
            cout << courseName << endl;
            courseList.push_back(courseName); // Store each student name in the vector
        }
        inputFile.close();
    }
    void addCourse(const string& name, const string& teacher, const string& course_code)
    {
        // Construct the student information string
        string courseInfo = name + " " + teacher + " " + course_code;
        // Add new student to the vector
        courseList.push_back(courseInfo);
        // Open the file in append mode
        ofstream outputFile("Course.txt", ios::app);
        if (!outputFile.is_open()) {
            cerr << "Failed to open the file.\n";
            return;
        }
        // Write the new student's information to the file
        outputFile << courseInfo << endl;
        // Close the file
        outputFile.close();
    }
};
class Section {
public:
    string sectionName;
    vector <Teacher*> teachers;
    vector <Rooms*> rooms;
    vector <Courses*> courses;
    vector < Labs* > lab;
    // Constructor
    Section(const string& name) : sectionName(name) {}
};
class Rooms {
public:
    int roomNumber;
    int r_Capacity = 50;
    Rooms(int roomNo, int r_Cap) :roomNumber(roomNo), r_Capacity(r_Cap) {}
};
void displayDayAndTimeTimetable(const vector<Courses>courses, const string& time, const string& day) {
    cout << "classes on " << day << "on " << time << endl;
    for (const auto& course : courses) {
        if (course.classTime == time) {
            cout << "course:" << course.courseName << course.courseID << course.teachers->tName << endl;
        }
    }
}
void displayDayTimetable(const vector<Courses>courses, const string& day) {
    cout << "classes on " << day << "on " << time << endl;
    for (const auto& course : courses) {
        if (course.dayOfWeek == day) {
            cout << "course:" << course.courseName << course.courseID << course.teachers->tName << endl;
        }
    }
}
void displayTeacherTimetable(const vector<Courses>& courses) {
    cout << "Teacher Timetable:\n";
    for (const auto& course : courses) {
        cout << "Course: " << course.courseName << endl;
        cout << "Teacher: " << course.teachers->tName << endl;
        cout << "Specialization: " << course.teachers->specialization << endl;
        cout << "Day: " << course.dayOfWeek << ", Time: " << course.classTime << endl;
        cout << "Room: " << course.rooms->roomNumber << endl;
        cout << "Section: " << course.section << endl;
        cout << "-----------------------\n";
    }
}
void displayStudentTimetable(const vector<Student>& students, const vector<Courses>courses) {
    cout << "Timetable for Student: " << endl;
    for (const auto& student : students) {
        cout << "Student: " << student.id << endl;
        cout << student.name << endl;
        cout << student.section << endl;
        for (const auto& course : courses) {
            cout << "Courses: " << endl;
            cout << "Course: " << course.courseName << endl;
            cout << "Teacher: " << course.teachers->tName << endl;
            cout << "Day: " << course.dayOfWeek << ", Time: " << course.classTime << endl;
            cout << "Room: " << course.rooms->roomNumber << endl;
            cout << "-----------------------\n";


        }
    }

}
// Display timetable for rooms
void displayRoomTimetable(const vector<Courses>& courses) {
    cout << "Room-wise Timetable:\n";
    for (const auto& course : courses) {
        cout << "Room: " << course.rooms->roomNumber << endl;
        cout << "Course: " << course.courseName << endl;
        cout << "Teacher: " << course.teachers->tName << endl;
        cout << "Day: " << course.dayOfWeek << ", Time: " << course.classTime << endl;
        cout << "Section: " << course.section << endl;
        cout << "-----------------------\n";
    }

}
void displayTimeTable(const vector<Courses>& timeTable) {
    for (const auto& course : timeTable) {
        cout << "Course: " << course.courseName << ", Time: " << course.classTime << ", Room: " << course.rooms->roomNumber << endl;
    }
}
void generateTeacherWiseTimeTable(const vector<Courses>& courses) {
    map<string, vector<Courses>> teacherTimeTable;
    for (const auto& course : courses) {
        teacherTimeTable[course.teachers->tName].push_back(course);
    }
    for (const auto& entry : teacherTimeTable) {
        cout << "Teacher: " << entry.first << endl;
        displayTimeTable(entry.second);
        cout << endl;
    }

}
void generateSectionWiseTimeTable(const vector<Courses>& courses) {
    map<int, vector<Courses>> sectionTimeTable;
    for (const auto& course : courses) {
        sectionTimeTable[course.rooms->roomNumber].push_back(course);
    }
    for (const auto& entry : sectionTimeTable) {
        cout << "Room: " << entry.first << endl;
        displayTimeTable(entry.second);
        cout << endl;
    }
}
void generateRoomWiseTimeTable(const vector<Courses>& courses) {
    map<int, vector<Courses>> roomTimeTable;
    for (const auto& course : courses) {
        roomTimeTable[course.rooms->roomNumber].push_back(course);
    }
    for (const auto& entry : roomTimeTable) {
        cout << "Room: " << entry.first << endl;
        displayTimeTable(entry.second);
        cout << endl;
    }
}
void userInterface() {
    cout << "================================\n";
    cout << "Time Table Allocation System" << endl;
    cout << "Menu:" << endl;
    cout << "1. Display Student wise timetable: " << endl;
    cout << "2. Display Teacher wise timetable: " << endl;
    cout << "3. Display Room wise timetable: " << endl;
    cout << "4. Display Day wise timetable: " << endl;
    cout << "5. Display Day and time wise timetable: " << endl;

    cout << "================================\n";

    cout << "6. Generate Section wise timetable: " << endl;
    cout << "7. Generate Teacher wise timetable: " << endl;
    cout << "8. Generate Room wise timetable: " << endl;
    cout << "================================\n";

    cout << "9.Show list of Students:\n";
    cout << "10. Add a Student: " << endl;
    cout << "11. Remove a Student:" << endl;
    cout << "12.Show list of teachers:\n";
    cout << "13.Show list of Courses:\n";
    cout << "14. Add a Course" << endl;

    cout << "15. Exit!" << endl;
    cout << "================================\n" << endl;
    cout << "Enter your choice: ";

}


int main() {
    Student st;
    Teacher teach;
    Courses course;
    // teachers 
    vector <Teacher> teachers{ Teacher("Mr. Tamim", "OOP"),
        Teacher("Mr. Raja", "Computer Programming") };
    //day & time
    string day, time;
    //students
    vector <Student> students = { Student("Tayyaba",804,"BSE2-A"),
        Student("Samreen", 805, "BSE2-A") };
    // rooms
    vector <Rooms> rooms = { Rooms(404,50),Rooms(405,25) };
    // courses
    vector <Courses> courses{ Courses("oop","oop101","8:00 am ",&teachers[0],&rooms[0],"BSE-2A")
        ,Courses("Computer Programming","cp666","9:00",&teachers[1],&rooms[1],"BSE-2B") };
    displayDayAndTimeTimetable(courses, "8:00", "monday");
    generateRoomWiseTimeTable(courses);
    generateSectionWiseTimeTable(courses);
    generateTeacherWiseTimeTable(courses);
    string name, teacher, course_code, studentName, newStudentName, className, enrollment;
    int choice = 0;
    userInterface();
    cin >> choice;
    switch (choice)
    {
    case 1:
        displayStudentTimetable(students, courses);
        break;
    case 2:
        displayTeacherTimetable(courses);
        break;
    case 3:
        displayRoomTimetable(courses);
        break;
    case 4:
        displayDayTimetable(courses, day);
        break;
    case 5:
        displayDayAndTimeTimetable(courses, time, day);
        break;
    case 6:
        generateSectionWiseTimeTable(courses);
        break;
    case 7:
        generateTeacherWiseTimeTable(courses);
        break;
    case 8:
        generateRoomWiseTimeTable(courses);
        break;
    case 9:
        st.showListOfStudents();
        break;
    case 10:
        cout << "Enter the name of the new student: ";
        cin >> newStudentName;
        cout << "Enter the class: ";
        cin >> className;
        cout << "Enter the enrollment: ";
        cin >> enrollment;
        st.addStudent(newStudentName, className, enrollment);
        st.showListOfStudents(); // Display updated list of students
        break;
    case 11:
        cout << "Enter the name of the student to remove: ";
        cin >> studentName;
        st.removeStudent(studentName);
        break;
    case 12:
        teach.showListOfTeachers();
        break;
    case 13:
        course.showListOfCourses();
        break;
    case 14:
        cout << "Enter the name of the new course: ";
        cin >> name;
        cout << "Enter the teacher: ";
        cin >> teacher;
        cout << "Enter the course code: ";
        cin >> course_code;
        course.addCourse(name, teacher, course_code);
        course.showListOfCourses(); // Display updated list of students
        break;
    case 15:
        cout << "15. Exit!" << endl;
        break;
    default:
        cout << "Invalid Choice!!!!!!!";
    }
    // Define specific sections, labs, and teachers for the SE department
    vector<Section> seSections = { Section("4-17"), Section("4-18"), Section("4-19") };
    vector<Labs> seLabs = { Labs("Lab1", 30), Labs("Lab2", 25) };

    // Populate initial data for courses with predefined schedules
    vector<Courses> seCourses = {
        Courses("Introduction to Software Engineering", "SE101", "8:30 am", &teachers[0], &rooms[0], "4-17"),
        Courses("Software Design", "SE201", "10:00 am", &teachers[0], &rooms[0], "4-18"),
        // Add more courses as needed
    };
    // Implement functions to generate timetables for teachers, sections, rooms, and labs based on predefined schedules
// You can use similar logic as in the existing functions for generating timetables
// I'll provide a basic example for generating teacher-wise timetable:

    void generateTeacherWiseTimeTable(const vector<Courses>&courses) {
        map<string, vector<Courses>> teacherTimeTable;
        for (const auto& course : courses) {
            teacherTimeTable[course.teachers->tName].push_back(course);
        }
        for (const auto& entry : teacherTimeTable) {
            cout << "Teacher: " << entry.first << endl;
            displayTimeTable(entry.second);
            cout << endl;
        }
    }

    return 0;
}