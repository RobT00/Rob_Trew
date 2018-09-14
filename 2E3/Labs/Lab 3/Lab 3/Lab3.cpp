#include <iostream>
#include "Student.h"
#include "Module.h"

using namespace std;

int main() {
	//Testing Student Class
	cout << "**Using Student Class (s0)**" << endl;
	Student s0;
	
	s0.readMarks();
	cout << endl;
	s0.printFinalGrade();
	cout << endl;
	
	s0.Buffer_Overload(); //Allows for s0 to be overwritten, to allow m0 to function
	
	//Testing Module Class
	cout << "**Using Module Class (m0)**" << endl;
	Module m0;
	
	cout << "\nPlease enter the last name of the Student's ID number you wish to find: ";
	string last_name;
	cin >> last_name;
	int foundID = m0.findByName(last_name);
	while (foundID == -5) {
		cout << "\nSTUDENT NOT FOUND!" << endl;
		cout << "Please enter the last name of the Student's ID number you wish to find: ";
		cin >> last_name;
		foundID = m0.findByName(last_name);
	}
	cout << "The Student ID for student: " << last_name << endl;
	cout << "Is: " << foundID << endl << endl;


	cout << "Please enter the ID of the student's last name you wish to find: ";
	int studentID;
	cin >> studentID;
	while (cin.fail()) {
		cout << "\n**INVALID ENTRY!**\n";
		cout << "Please enter the ID of the student's last name you wish to find: ";
		cin >> studentID;	
	}
	string foundName = m0.findByID(studentID);
	while (foundName == "NO") {
		cout << "\nSTUDENT NOT FOUND!" << endl;
		cout << "Please enter the ID of the student's last name you wish to find: ";
		cin >> studentID;
		foundName = m0.findByID(studentID);
	}
	cout << "The last name of the student with ID no: " << studentID << endl;
	cout << "Is: " << foundName << endl << endl;

	return 0;
}