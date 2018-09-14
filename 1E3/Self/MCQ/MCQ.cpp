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

//    cout << model[0] << endl;
//    cout << model[19] << endl;
//    int j = 0;
//    data >> student[j];
//    while (student[j] != -1)
//    {
//        data >> ans[i];
//        i++;
//        j++;
//        data >> student[j];
//    }
    j = 0;
    data >> student[j];
    while (student[j] != -1)
    {
//        cout << student[j] << endl;
        read(ans, SIZE);
//        cout << ans[19] << endl;
        mark[j] = answers(model, ans, SIZE, mark);
        j++;
        data >> student[j];
    }
//    cout << j << endl;
    students = j;
//    for (i = 0; i < SIZE; i++)
//        data >> ans[i];
//    cout << ans[0] << endl;
//    cout << ans[2] << endl;
//    cout << ans[18] << endl;
//    cout << ans[19] << endl;
//
//    data >> student[1];
//    for (i = 0; i < SIZE; i++)
//        data >> ans[i];
//    cout << student[1] << endl;
//    cout << ans[0] << endl;
//    cout << ans[2] << endl;
//    cout << ans[18] << endl;
//    cout << ans[19] << endl;
//
//        data >> student[2];
//    for (i = 0; i < SIZE; i++)
//        data >> ans[i];
//    cout << student[2] << endl;
//    cout << ans[0] << endl;
//    cout << ans[2] << endl;
//    cout << ans[18] << endl;
//    cout << ans[19] << endl;
//
//    cout << "\nMARKS" << endl;
//    cout << mark[0] << endl;
//    cout << mark[1] << endl;
//    cout << mark[2] << endl;

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
    int i, j = 0;
    while(j == 0)
    {
        for (i = 0; i < SIZE; i++)
        {
//            cout << ans[i] << endl;
//            cout << model[i] << endl;
            if (ans[i] == model[i])
            {
//                cout << score << endl;
                score = score + 2;
//                cout << "Correct " << score << endl;
//                cout << endl;
            }
            else if (ans[i] == 'x')
            {
                score = score + 0;
//                cout << "X " << score << endl;
            }
            else
            {
                score--;
//                cout << "Wrong " << score << endl;
            }
//            cout << "I = " << i << endl;
        }
//        cout << score << endl;
        return score;
    }
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

