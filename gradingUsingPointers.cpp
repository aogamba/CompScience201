#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;



typedef struct studentInfo{

	int studentID;
	string answers;
	int score;
	float percent;
	char grade;
	
}Student;
//checking for student number...can't have letters or other types of characters...only numbers
bool isDigits(const string& str) {
	return all_of(str.begin(), str.end(), ::isdigit);
}
bool isValidAnswerChar(char c) {
	c = toupper(c); // Normalize case
	return c == 'A' || c == 'B' || c == 'C' || c == 'D';
}

void setScore(Student* s, string& correctAnswer)
{
	int length = 20;
	int score = 0;
	for (int i = 0; i < length;++i)
	{
		if (s->answers[i] == correctAnswer[i])
			score = score + 2;
		else if (s->answers[i] != correctAnswer[i] && s->answers[i] == ' ')
		{
			score = score + 1;
		}
		else {
			score = score;
		}

	}
	s->score = score;
}
void setPercentage( Student* s)
{
	int maxScore = 40;
	s->percent = (s->score / (float)maxScore) * 100;
	
}

void setGrade(Student* s)
{
	int switchToInt = static_cast<int>(s->percent) / 10;

	switch (switchToInt)
	{
	case 10: //100%
	case 9://90-99%
		s->grade = 'A';
		break;
	case 8: //80-89%
		s->grade = 'B';
		break;
	case 7:
		s->grade = 'C';
		break;
	case 6:
		s->grade = 'D';
	default:
		s->grade = 'F';
		break;
	}
}



int main() {
	ifstream inputFile("C:/Users/Ashley/Desktop/student.txt");
	ofstream errorFile("error.txt");
	ofstream reportFile("report.txt");

	if (!inputFile || !errorFile || !reportFile) {
		cerr << "Error opening one or more files." << endl;
		return 1;
	}

	string correctAnswers;
	getline(inputFile, correctAnswers); // First line: correct answers

	vector<Student*> studentRecords;
	string line;

	while (getline(inputFile, line)) {
		istringstream iss(line);
		string idStr, answers;
		iss >> idStr;
		getline(iss, answers); // remainder is the answers, possibly with spaces

		answers.erase(remove(answers.begin(), answers.end(), ' '), answers.end());

		string cleanedAnswers;
		for (char c : answers) {
			if (isalpha(c)) {
				char upper = toupper(c);
				if (isValidAnswerChar(upper)) {
					cleanedAnswers += upper;
				}
			}
		}
		answers = cleanedAnswers;

		if (!isDigits(idStr)) {
			errorFile << "Error found in this line: " << line << endl;
			continue;
		}

		Student* s = new Student;
		s->studentID = stoi(idStr);
		s->answers = answers;

		setScore(s, correctAnswers);
		setPercentage(s);
		setGrade(s);

		studentRecords.push_back(s);
	}

	// Write report header
	reportFile << left << setw(10) << "ID"
		<< setw(25) << "Answers"
		<< setw(10) << "Score"
		<< setw(10) << "Percent"
		<< "Grade" << endl;

	// Write all student records
	for (Student* s : studentRecords) {
		reportFile << left << setw(10) << s->studentID
			<< setw(25) << s->answers
			<< setw(10) << s->score
			<< setw(10) << fixed << setprecision(2) << s->percent
			<< s->grade << endl;
	}

	// Free memory
	for (Student* s : studentRecords) {
		delete s;
	}

	return 0;
}

