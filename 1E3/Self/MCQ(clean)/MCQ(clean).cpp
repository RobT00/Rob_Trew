#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int SIZE = 20;
ifstream data;

void read (char ans[], int SIZE);
int answers (const char model[],const char ans[], int asize, int mark[]);
void scores (const int mark[], const int student[], int students);

int main()
{
	int i, j, students;
	int student[SIZE], mark[SIZE];
	char ans[SIZE], model[SIZE];

    data.open ("MCQ.txt");
	for (i = 0; i < SIZE; i++)
        data >> model[i];

    j = 0;
    data >> student[j];
    while (student[j] != -1)
    {
        read(ans, SIZE);
        mark[j] = answers(model, ans, SIZE, mark);
        j++;
        data >> student[j];
    }
    students = j;

	data.close();

	scores(mark, student, students);

    return 0;
}

void read (char ans[], int SIZE)
{
    int i;
    for (i = 0; i < SIZE; i++)
        data >> ans[i];
}
int answers (const char model[],const char ans[], int asize, int mark[])
{
    int score = 0;
    int i;
    for (i = 0; i < SIZE; i++)
    {
        if (ans[i] == model[i])
            score = score + 2;

        else if (ans[i] == 'x')
            score = score + 0;

        else
            score--;
    }
    return score;
}

void scores (const int mark[], const int student[], int students)
{
    cout << std::fixed << setprecision(0);
    cout << "Student Number" << setw(2) << " | " << "Score" << endl;
    cout << setfill('-') << setw(22) << "-" << endl;
    cout << setfill(' ');
    for (int i = 0; i < students; i++)
        cout << student[i] << setw(14) << right << " | " << mark[i] << endl;
}

