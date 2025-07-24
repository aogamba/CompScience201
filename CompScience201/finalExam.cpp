#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Struct to hold student quiz data
struct StudentQuizInfo {
    int studentID;
    string studentAnswers; // The 5 answers the student provided
    int correctCount;      // Number of correct answers
};

// Writes the quiz data file automatically inside the program
void generateQuizDataFile(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error creating quiz data file: " << filename << endl;
        return;
    }

    // Correct answer key
    outfile << "ABCDE\n";

    // Student data
    outfile << "1001 ABCDA\n";
    outfile << "1002 ABCCE\n";
    outfile << "1003 BCDAB\n";
    outfile << "1004 AACCE\n";
    outfile << "1005 DBDEA\n";
    outfile << "1006 ABCBC\n";
    outfile << "1007 EDCBA\n";
    outfile << "1008 CEBDA\n";
    outfile << "1009 DEABC\n";
    outfile << "1010 BACED\n";
    outfile << "1011 ADBCE\n";
    outfile << "1012 CEACB\n";
    outfile << "1013 EBCDA\n";
    outfile << "1014 DABCD\n";
    outfile << "1015 CBAED\n";
    outfile << "1016 DEBAC\n";
    outfile << "1017 BDCAE\n";
    outfile << "1018 EADCB\n";
    outfile << "1019 ACBED\n";
    outfile << "1020 BCDEA\n";
    outfile << "1021 DABEC\n";
    outfile << "1022 EDACB\n";
    outfile << "1023 ABCDE\n";
    outfile << "1024 BCDEA\n";
    outfile << "1025 CDEAB\n";
    outfile << "1026 DEABC\n";
    outfile << "1027 EABCD\n";
    outfile << "1028 ABCDD\n";
    outfile << "1029 ABDCE\n";
    outfile << "1030 ABBCD\n";

    outfile.close();
}

// Reads quiz data from input file, populates correctAnswers and students vector
bool readQuizData(const string& filename, string& correctAnswers, vector<StudentQuizInfo*>& students) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening input file: " << filename << endl;
        return false;
    }

    if (!getline(infile, correctAnswers)) {
        cerr << "Error reading correct answers line." << endl;
        return false;
    }

    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        int id;
        string answers;

        if (!(iss >> id >> answers)) {
            cerr << "Error parsing student data: " << line << endl;
            continue;
        }

        StudentQuizInfo* student = new StudentQuizInfo;
        student->studentID = id;
        student->studentAnswers = answers;
        student->correctCount = 0;

        students.push_back(student);
    }

    infile.close();
    return true;
}

// Calculates correctCount for a single student by comparing to correctAnswers
void calculateScores(const string& correctAnswers, StudentQuizInfo* studentPtr) {
    int count = 0;
    for (size_t i = 0; i < correctAnswers.size() && i < studentPtr->studentAnswers.size(); ++i) {
        if (studentPtr->studentAnswers[i] == correctAnswers[i]) {
            ++count;
        }
    }
    studentPtr->correctCount = count;
}

// Writes student results to output file
bool writeResults(const string& filename, const vector<StudentQuizInfo*>& students) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Error opening output file: " << filename << endl;
        return false;
    }

    outfile << "STUD ID CORRECT\n";
    for (const auto student : students) {
        outfile << student->studentID << " " << student->correctCount << "\n";
    }

    outfile.close();
    return true;
}

// Deallocates dynamically allocated memory for students
void cleanUp(vector<StudentQuizInfo*>& students) {
    for (auto student : students) {
        delete student;
    }
    students.clear();
}

int main() {
    string correctAnswers;
    vector<StudentQuizInfo*> students;

    // STEP 1: Generate the input data file dynamically
    generateQuizDataFile("quiz_data.txt");

    // STEP 2: Read quiz data from file
    if (!readQuizData("quiz_data.txt", correctAnswers, students)) {
        return 1;
    }

    // STEP 3: Grade each student
    for (auto student : students) {
        calculateScores(correctAnswers, student);
    }

    // STEP 4: Write output file
    if (!writeResults("quiz_results.txt", students)) {
        cleanUp(students);
        return 1;
    }

    // STEP 5: Free memory
    cleanUp(students);

    cout << "Quiz grading completed successfully.\n";
    return 0;
}

