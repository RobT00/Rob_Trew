/*Time to read in and order list: 4.913s

Comparisons to find CRONIN, Abraham: 19			Time: 0.002s
Comparisons to find BREE, Colin: 15				Time: 0.001s
{Comparisons to find GREENE, Anne: 13			Time: 0.001s}
Comparisons to find HOLOHAN, Etienne: 21		Time: 0.001s
{Comparisons to find SLOANE, Lynn: 14			Time: 0.002s}
Comparisons to find AAAA, "": 10 [Not Found]	Time: 0.001s
Comparisons to find ZZZZ, "": 9 [Not Found]		Time: 0.001s
*/

//BINARY SEARCH TREE IS MORE EFFICIENT FOR SEARCHING

#include <iostream>
#include <string>
#include "StudentNode.h"
#include "StudentLinkedList.h"
#include <fstream>
#include <ctime>

using namespace std;

int main() {
	StudentLinkedList sll0;
	StudentNode* select;
	string lname, fname;
	double grade;
	int id;
	ifstream Students ("Student10000.txt");
	ofstream Output ("OrderStudent.txt");
	
	if (!(Students.is_open())) {
		cout << "FILE NOT FOUND/OPENED!! \nTERMINATING PROGRAM" << endl;
		return 0;
	}

	//cout << string(50, '*') << endl;
	cout << "***** Genertaing List sll0 *****" << endl;
	StudentNode* list = nullptr;
	int start_s = clock();
	for (int i = 0; i < 10000; i++) {
		Students >> lname >> fname >> id >> grade;
		sll0.addStudent(lname, fname, id, grade);
		cout << i << endl;
	}
	int stop_s = clock();
	double time_taken = double(stop_s - start_s) / CLOCKS_PER_SEC;
	cout << endl;
	//sll0.printAllStudents();
	//sll0.checkListLength();
	//cout << "***** Initial List Length: " << sll0.getListLength() << " *****" << endl;
	cout << string(60, '-') << endl << endl;
	Students.close();
	
	//if (!(Output.is_open()))
	//	cout << "OUTPUT FILE NOT FOUND/OPENED!!" << endl;
	//else {
	//	cout << "Outputting list to file" << endl;
	//	sll0.outputLinkedList(Output);
	//	cout << "List outputted to file" << endl;
	//}
	cout << "Time to read in and order list: " << time_taken << "s" << endl << endl;
	cout << "Searching for Students: " << endl;

	cout << "CRONIN, Abraham" << endl;
	start_s = clock();
	select = sll0.findStudent("CRONIN", "Abraham");
	if (select == NULL)
		cout << "Not found" << endl << endl;
	else {
		cout << "Student found: " << endl;
		sll0.printOneStudent(select);
	}
	stop_s = clock();
	time_taken = double(stop_s - start_s) / CLOCKS_PER_SEC;
	cout << "Time to search for student: " << time_taken << "s" << endl << endl;
	cout << endl;

	//cout << "ALLEN, Roisin" << endl;
	//select = sll0.findStudent("ALLEN", "Roisin");
	//if (select == NULL)
	//	cout << "Not found" << endl << endl;
	//else {
	//	cout << "Student found: " << endl;
	//	sll0.printOneStudent(select);
	//}
	//cout << endl;
	//cout << "CAHILL, Rebecca" << endl;
	//select = sll0.findStudent("CAHILL", "Rebecca");
	//if (select == NULL)
	//	cout << "Not found" << endl << endl;
	//else {
	//	cout << "Student found: " << endl;
	//	sll0.printOneStudent(select);
	//}
	//cout << endl;
	//cout << "CAHILL, Roisin" << endl;
	//select = sll0.findStudent("CAHILL", "Roisin");
	//if (select == NULL)
	//	cout << "Not found" << endl << endl;
	//else {
	//	cout << "Student found: " << endl;
	//	sll0.printOneStudent(select);
	//}
	//cout << "WYLIE, Jasper" << endl;
	//select = sll0.findStudent("WYLIE", "Jasper");
	//if (select == NULL)
	//	cout << "Not found" << endl << endl;
	//else {
	//	cout << "Student found: " << endl;
	//	sll0.printOneStudent(select);
	//}
	//cout << endl;

	cout << "GREENE, Anne" << endl;
	start_s = clock();
	select = sll0.findStudent("GREENE", "Anne");
	if (select == NULL)
		cout << "Not found" << endl << endl;
	else {
		cout << "Student found: " << endl;
		sll0.printOneStudent(select);
	}
	stop_s = clock();
	time_taken = double(stop_s - start_s) / CLOCKS_PER_SEC;
	cout << "Time to search for student: " << time_taken << "s" << endl << endl;

	cout << "BREE, Collin" << endl;
	start_s = clock();
	select = sll0.findStudent("BREE", "Collin");
	if (select == NULL)
		cout << "Not found" << endl << endl;
	else {
		cout << "Student found: " << endl;
		sll0.printOneStudent(select);
	}
	stop_s = clock();
	time_taken = double(stop_s - start_s) / CLOCKS_PER_SEC;
	cout << "Time to search for student: " << time_taken << "s" << endl << endl;

	cout << "HOLOHAN, Etienne" << endl;
	start_s = clock();
	select = sll0.findStudent("HOLOHAN", "Etienne");
	if (select == NULL)
		cout << "Not found" << endl << endl;
	else {
		cout << "Student found: " << endl;
		sll0.printOneStudent(select);
	}
	stop_s = clock();
	time_taken = double(stop_s - start_s) / CLOCKS_PER_SEC;
	cout << "Time to search for student: " << time_taken << "s" << endl << endl;

	cout << "SLOANE, Lynn" << endl;
	start_s = clock();
	select = sll0.findStudent("SLOANE", "Lynn");
	if (select == NULL)
		cout << "Not found" << endl << endl;
	else {
		cout << "Student found: " << endl;
		sll0.printOneStudent(select);
	}
	stop_s = clock();
	time_taken = double(stop_s - start_s) / CLOCKS_PER_SEC;
	cout << "Time to search for student: " << time_taken << "s" << endl << endl;

	cout << "AAAA, " << endl;
	start_s = clock();
	select = sll0.findStudent("AAAA", "");
	if (select == NULL)
		cout << "Not found" << endl << endl;
	else {
		cout << "Student found: " << endl;
		sll0.printOneStudent(select);
	}
	stop_s = clock();
	time_taken = double(stop_s - start_s) / CLOCKS_PER_SEC;
	cout << "Time to search for student: " << time_taken << "s" << endl << endl;

	cout << "ZZZZ, " << endl;
	start_s = clock();
	select = sll0.findStudent("ZZZZ", "");
	if (select == NULL)
		cout << "Not found" << endl << endl;
	else {
		cout << "Student found: " << endl;
		sll0.printOneStudent(select);
	}
	stop_s = clock();
	time_taken = double(stop_s - start_s) / CLOCKS_PER_SEC;
	cout << "Time to search for student: " << time_taken << "s" << endl << endl;
	return 0;
}