#pragma once
#include <iostream>
#include <string>

using namespace std;

class Student {
private:
	static const int SIZE = 3;
	int studentID;			//ID number for student
	double labs[SIZE];		//Lab marks out of 100
	double exam;			//Exam mark out of 100
	double finalGrade;		//Labs worth 40%, Exam worth 60%
	string f_name;	//Student first name
	string s_name;	//Student Last name
	static int numStudents; //Static variable that counts students
							//Should be initialized once to 0

public:
	Student();				//Constructor that sets all marks to 0,
							//studentID is set to be numStudents, and
							//then numStudents is incremented
	void Buffer_Overload();
	void readMarks();		//Lets user input all lab marks and exam mark
	void printFinalGrade(); //Calculates the final grade and prints it
	string get_StudentLN() const;
	int get_StudentID() const;
};