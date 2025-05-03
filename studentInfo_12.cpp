#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
    string address;

    // Function to read student data from a line
    void readFromStream(const string& line) {
        stringstream ss(line);
        ss >> rollNumber;
        getline(ss, name, ',');
        getline(ss, division, ',');
        getline(ss, address);
    }

    // Function to write student data to a file stream
    void writeToStream(ofstream& outFile) {
        outFile << rollNumber << ","
                << name << ","
                << division << ","
                << address << endl;
    }
};

void addStudent(const string& filename) {
    ofstream outFile(filename, ios::app); // Open file in append mode
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student s;
    cout << "Enter Roll Number: ";
    cin >> s.rollNumber;
    cin.ignore();  // Ignore the newline character after the number input
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Division: ";
    getline(cin, s.division);
    cout << "Enter Address: ";
    getline(cin, s.address);

    s.writeToStream(outFile);
    cout << "Student added successfully!" << endl;

    outFile.close();
}

void displayStudent(const string& filename, int rollNumber) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        Student s;
        s.readFromStream(line);
        if (s.rollNumber == rollNumber) {
            cout << "Student Found!" << endl;
            cout << "Roll Number: " << s.rollNumber << endl;
            cout << "Name: " << s.name << endl;
            cout << "Division: " << s.division << endl;
            cout << "Address: " << s.address << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
    }

    inFile.close();
}

void deleteStudent(const string& filename, int rollNumber) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    ofstream tempFile("temp.txt");
    bool found = false;

    while (getline(inFile, line)) {
        Student s;
        s.readFromStream(line);
        if (s.rollNumber == rollNumber) {
            found = true;  // Skip adding this student to the temp file
        } else {
            s.writeToStream(tempFile);  // Write to temp file
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        // Replace original file with temp file
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Student deleted successfully!" << endl;
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
        remove("temp.txt");  // Clean up temporary file
    }
}

int main() {
    string filename = "students.txt";
    int choice, rollNumber;

    while (true) {
        cout << "\n1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(filename);
                break;
            case 2:
                cout << "Enter Roll Number to search: ";
                cin >> rollNumber;
                displayStudent(filename, rollNumber);
                break;
            case 3:
                cout << "Enter Roll Number to delete: ";
                cin >> rollNumber;
                deleteStudent(filename, rollNumber);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}



// output:- 



// 1. Add Student
// 2. Display Student
// 3. Delete Student
// 4. Exit
// Enter your choice: 1
// Enter Roll Number: 101
// Enter Name: John Doe
// Enter Division: A
// Enter Address: 123 Main Street
// Student added successfully!

// 1. Add Student
// 2. Display Student
// 3. Delete Student
// 4. Exit
// Enter your choice: 2
// Enter Roll Number to search: 101
// Student Found!
// Roll Number: 101
// Name: John Doe
// Division: A
// Address: 123 Main Street

// 1. Add Student
// 2. Display Student
// 3. Delete Student
// 4. Exit
// Enter your choice: 3
// Enter Roll Number to delete: 101
// Student deleted successfully!

// 1. Add Student
// 2. Display Student
// 3. Delete Student
// 4. Exit
// Enter your choice: 2
// Enter Roll Number to search: 101
// Student with Roll Number 101 not found!
