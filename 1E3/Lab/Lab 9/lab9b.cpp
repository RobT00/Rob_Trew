#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void read_answ (char array[], int size);
int giveGrade (char array[], char key[], int size);

int main()
{
	int student_num;
	int mark;
	char key[20], student_ans[20];
	
	read_answ(key,20);
	
	cin >> student_num;
	
	while (student_num > 0) {
		read_answ (student_ans, 20);
		mark = giveGrade (student_ans, key, 20);
		cout << student_num << " " << mark << endl;
		
		cin >> student_num;
	}
	return 0;
}

void read_answ (char array[], int size)
{
	for (int i = 0; i<20; i++)
		cin >> array[i];
}
int giveGrade (char array[], char key[], int size)
{
	int mark = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] == key[i])
			mark = mark +2;
		else if (array[i] != 'x')
			mark = mark - 1;
	}
	return mark;
}