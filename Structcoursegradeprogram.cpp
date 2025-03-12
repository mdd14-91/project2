#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;


struct Student;
// Function prototypes

//getData Function
//description-reads the student count and test count from file then uses that information to read the data for the struct. Stores student names&ID and student scores 
//in the struct arrays.
//inputs=studentCount,testCount and data from file, and Student struct
//outputs=studentCount and TestCount stored in variables. The student name array and testscores&ID data is stored in appropriate arrays. 
//preconditions=text file that provides student count and test count first followed by studentnames with test scores. And need student struct for the pointer.
//postconditions=studentCount and TestCount stored in variables. The student name array and ID and testscores data is stored in appropriate arrays.
Student* getData(ifstream& file, int& studentCount, int& testCount);

//CalculateAverages Function
//description-Calculates & stores the average score from adding up the testscores for the student and dividing by the total number of scores for that student
//inputs=student count and Student struct.
//outputs=averageScore array in the struct
//preconditions=need student struct and studentCount.
//postconditions=averageScore array in struct is populated.
void calculateAverages(Student* students, int studentCount, int testCount);

//Lettergradeconverter Function
//description-gets the Averagescore calculated from Calculatescores function and returns a lettergrade and stores that lettergrade in the letterGrade array.
//inputs=student struct and studentCount 
//outputs=lettergrade array values populated
//preconditions=need student struct and studentcount
//postconditions=outputs all the lettergrade values into the lettergrade array
void lettergradeconverter(Student* students, int studentCount);

//printReport function
//description=prints student grade report to screen by going through the student lettergrade,name, averageScore, and ID array and printing them out for each student 
//inputs=student struct and studentcount
//outputs=displays student grade report to screen
//preconditions=student struct needed and studentCount
//postconditions=print student grade report to screen
void printReport(Student* students, int studentCount);

//Cleanup function
//description-iterates through the array of structs, deleting testscore array then deletes student data array
//inputs=student struct and studentcount
//outputs=deletes array of structs
//preconditions=need student struct and studentCount
//postconditions=removes array of structs from memory.
void cleanup(Student* students, int studentCount);

// Struct definition
struct Student {
    string name;
    int* testScores; // Pointer for dynamically allocated array of test scores
    double averageScore; // Average score
    string letterGrade; // Letter grade based on average score
    int id;// Student ID
};

// Main function
// if there is no file present the program simply gives an error message and terminates
//This program first reads data from a file that includes the number of scores & students along with student names and all the student's scores. 
//First, it reads the number of students&scores and stores it in studentCount and testCount. THen it uses those two variables as counters to control the loops
//for reading the data into the other struct arrays. After that it takes the data and gets the average and lettergrade for each student along with their names. 
//after computing that it displays all the student's names, averages and letter grade that they earned. After that, the program deallocates memory from the arrays
//and structs, and it clears them and then ends.
int main() {
    ifstream file("Students.txt");

    // Check if the file opens successfully
    if (!file) {
        cout << "Error opening file" << endl;
        return 1;
    }

    int studentCount = 0;
    int testCount = 0;

    // Get student data from the file
    Student* students = getData(file, studentCount, testCount);

    // Calculate averages and letter grades
    calculateAverages(students, studentCount, testCount);
    lettergradeconverter(students, studentCount);

    // Print the formatted report
    printReport(students, studentCount);

    // Cleanup: free dynamically allocated memory
    cleanup(students, studentCount);

    file.close(); // Close the file
    return 0;
}


// Function to read data from the file and populate an array of Student structs
Student* getData(ifstream& file, int& studentCount, int& testCount) {
    file >> studentCount >> testCount; // Read number of students and number of test scores
    file.ignore(); // Ignore newline after reading counts

    Student* students = new Student[studentCount]; // Allocate arrays for students struct

    for (int i = 0; i < studentCount; ++i) {
        // Read student name and ID directly
        file >> students[i].name >> students[i].id; 

        // Allocate memory for test scores
        students[i].testScores = new int[testCount];

        // Read test scores directly into the array
        for (int j = 0; j < testCount; ++j) {
            file >> students[i].testScores[j]; 
        }
    }
    return students;
}

void calculateAverages(Student* students, int studentCount, int testCount) {
    for (int i = 0; i < studentCount; ++i) {
        int total = 0;
        for (int j = 0; j < testCount; ++j) {
            total += students[i].testScores[j]; // Sum test scores
        }
        students[i].averageScore = static_cast<double>(total) / testCount; // Calculate average
    }
}


void lettergradeconverter(Student* students, int studentCount) {
    for (int i = 0; i < studentCount; i++) {
        double averageScore = students[i].averageScore;
        if (averageScore >= 90 && averageScore <= 100) {
            students[i].letterGrade = "A";
        }
        else if (averageScore >= 80 && averageScore <= 89.99) {
            students[i].letterGrade = "B";
        }
        else if (averageScore >= 70 && averageScore <= 79.99) {
            students[i].letterGrade = "C";
        }
        else if (averageScore >= 60 && averageScore <= 69.99) {
            students[i].letterGrade = "D";
        }
        else if (averageScore >= 0 && averageScore <= 59.99) {
            students[i].letterGrade = "F";
        }
    }
}


void printReport(Student* students, int studentCount) {
    cout << left << setw(15) << "Student" << setw(10) << "ID" << setw(10) << "Score" << "Grade" << endl;
    cout << " " << endl;
    for (int i = 0; i < studentCount; ++i) {
        cout << left << setw(15) << students[i].name
            << setw(10) << students[i].id
            << setw(10) << fixed << setprecision(1) << students[i].averageScore
            << students[i].letterGrade << endl;
    }
}


void cleanup(Student* students, int studentCount) {
    for (int i = 0; i < studentCount; ++i) {
        delete[] students[i].testScores; // Free memory for test scores
    }
    delete[] students; // Free memory for student array
}